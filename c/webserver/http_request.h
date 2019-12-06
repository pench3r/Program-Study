#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#define MAX_BUF 8194

typedef struct http_request_ {
	int fd;	/* socket */
	int epfd; /*	epoll fd */
	int state; /* parse state */	
	int start;
	int end;
	char request[MAX_BUF];
	void *request_uri_start;
	void *request_uri_end;
	unsigned long recv_total_bytes;
}http_request_t;


http_request_t* new_http_request_t(int fd, int epfd);

#endif
