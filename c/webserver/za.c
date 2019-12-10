#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include "thread_pool.h"
#include "parse_http_request.h"

#define MAX_CONN 255
#define MAX_EPOLL_EVENTS_NUM 64
#define WWW_ROOT "/home/pench3r/www"
#define MAX_FILE_NAME 1024
#define SERVER_PORT 8888


int sfd, epfd;

int create_and_bind_socket() {
	struct sockaddr_in server_sockaddr;
	int listen_fd;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(SERVER_PORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listen_fd, (const struct sockaddr*)&server_sockaddr, (socklen_t)sizeof(server_sockaddr));	
	return listen_fd;
}


int make_socket_non_blocking(int sfd) {
	int flags;
	flags = fcntl(sfd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(sfd, F_SETFL, O_NONBLOCK);
	return 0;
}


int process_http_request_file_out_to_response(http_request_t *hreq, http_response_t *hrsp) {
	char FileName[MAX_FILE_NAME] = {0};
	if (hreq->rq_uri_len >= 1024) {
		perror("uri too long");
		return -1;
	}
	sprintf(FileName, "%.*s", hreq->rq_uri_len, (char *)hreq->rq_uri); 
	chdir(WWW_ROOT);
	chroot(WWW_ROOT);
	printf("filename: %s\n", FileName);
	struct stat statbuf;
	int r = stat(FileName, &statbuf);
	if (r == 0) {
		int filefd = open(FileName, O_RDONLY, 0);
		char *fileaddr = mmap(NULL, (size_t)statbuf.st_size, PROT_READ, MAP_PRIVATE, filefd, 0);
		if (fileaddr != MAP_FAILED) {
			hrsp->rsp_file_addr = fileaddr;		
			hrsp->rsp_file_size = (int)statbuf.st_size;
			return 0;
		}
	}
	return -1;
}

void* do_process(void* data) {
	ssize_t recv_count;
	http_request_t *c_hreq = (http_request_t *)data;
	char *recv_buf = c_hreq->request_buf;
	int cfd = c_hreq->fd;
	while(1) {
		recv_count = recv(cfd, (void *)recv_buf, MAX_BUF, 0);
		if (recv_count == -1) {
			if (errno != EAGAIN) {
				printf("disconn.\n");
				close(cfd);
			}
			break;
		}
		if (recv_count == 0) {
			printf("disconn.\n");
			close(cfd);
			break;
		}	
		c_hreq->recv_bytes = recv_count;

		if (parse_http_request(c_hreq) != HP_PARSE_OK)
			continue;	

		http_response_t *h_rsp = new_http_response_t(cfd);

		process_http_request_file_out_to_response(c_hreq, h_rsp);

		build_response_and_out_to_socket(h_rsp);

		destory_http_response_t(h_rsp);

		for (int i = 0; i<MAX_BUF; ++i) {
			recv_buf[i] = '0';
		}
	}
}

int create_listen_nonblock_socket() {
	int lfd, result;
	lfd = create_and_bind_socket();
	result = make_socket_non_blocking(lfd);
	result = listen(lfd, MAX_CONN);
	return lfd;
}


int recv_client_socket() {
	struct sockaddr_in peer_socket;
	int peer_socket_len = sizeof(peer_socket);
	int cfd = accept(sfd, (struct sockaddr*)&peer_socket,(socklen_t*)&peer_socket_len);
	printf("recv conn from: %s\n", inet_ntoa(peer_socket.sin_addr));
	return cfd;
}


void epoll_add_event_with_client_socket(int sfd) {
	struct epoll_event *event;
	event = (struct epoll_event *)malloc(sizeof(struct epoll_event));	
	event->events = EPOLLIN | EPOLLET;
	event->data.u64 = 0;
	event->data.fd = sfd;
	http_request_t *c_hrt = new_http_request_t(sfd, epfd);
	event->data.ptr = (void *)c_hrt;
	epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, event);
}

void epoll_add_event_with_server_socket(int sfd) {
	struct epoll_event *event;
	event = (struct epoll_event *)malloc(sizeof(struct epoll_event));	
	event->events = EPOLLIN | EPOLLET;
	event->data.u64 = 0;
	event->data.fd = sfd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, event);
}


void proc_events_with_thread_pool(struct epoll_event *events, int events_num, thread_pool_t * tpt) {
	for (int i=0; i<events_num; ++i) {
		if ((events[i].events & EPOLLERR) ||
				(events[i].events & EPOLLHUP) ||
				(!(events[i].events & EPOLLIN))) {
			fprintf(stderr, "epoll error\n");
			close(events[i].data.fd);
		} else if (sfd == events[i].data.fd) {
			// server socket have new conn
			int cfd = recv_client_socket();
			make_socket_non_blocking(cfd);
			epoll_add_event_with_client_socket(cfd);
		} else {
			// process incoming data from client socket
			add_task_to_thread_pool(tpt,do_process,(void*)(events[i].data.ptr));
		}
	}	
} 


void monitor_and_proc_event_with_thread_pool(thread_pool_t *tpt) {
	struct epoll_event *events;
	int epoll_result;
	events = calloc(MAX_EPOLL_EVENTS_NUM, sizeof(struct epoll_event));
	epoll_result = epoll_wait(epfd, events, MAX_EPOLL_EVENTS_NUM, -1);
	if (epoll_result < 0) {
		exit(-1);
	}
	if (epoll_result > 0) {
		proc_events_with_thread_pool(events, epoll_result, tpt);
	}
}


int main(int argc, char *argv[]) {
	int cfd, result;
	sfd = create_listen_nonblock_socket();

	thread_pool_t *tpt = (thread_pool_t *)malloc(sizeof(thread_pool_t));
	create_thread_pool(&tpt, 5);

	struct epoll_event event;
	struct epoll_event *events;
	int epoll_result;
	epfd = epoll_create1(0);
	epoll_add_event_with_server_socket(sfd);
	events = calloc(MAX_EPOLL_EVENTS_NUM, sizeof(struct epoll_event));
	while (1) {
		monitor_and_proc_event_with_thread_pool(tpt);
	}

	return 0;
}
