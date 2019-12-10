#ifndef HTTP_PARSE_REQUEST_H
#define HTTP_PARSE_REQUEST_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/socket.h>

#define HP_PARSE_ERR -1
#define HP_PARSE_OK 0
#define HP_PARSE_AGAIN 1

#define MAX_HEADER_NUM 1024
#define MAX_BUF 8192

typedef struct request_header_ {
  void *rh_key;
  int rh_key_len;
  void *rh_val;
  int rh_val_len;
} request_header_t;

typedef struct http_request_t_ {
	int fd;
	int epfd;
  int start;
  int end;
  int state;
  int recv_bytes;
  void *rq_uri;
  int rq_uri_len;
  request_header_t *headers[MAX_HEADER_NUM];
  int header_num;
	char request_buf[MAX_BUF];
} http_request_t;


typedef struct http_response_t_ {
	int fd;
	int status_code;
	char *rsp_file_addr;
	int rsp_file_size;
} http_response_t;


http_request_t* new_http_request_t(int fd, int epfd);

http_response_t* new_http_response_t(int fd);

void send_content(int fd, char *content, int content_len);

void destory_http_response_t(http_response_t *hrsp);

void build_response_and_out_to_socket(http_response_t *h_rsp);

int parse_http_request(http_request_t *h_req);

// int http_prase_request_first_line(http_request_t *hrt);
int parse_http_request_first_line(http_request_t *h_req);

int parse_http_request_header(http_request_t *h_req);

int orgstr1_compare_tarstr2_with_fix_len(void *start, void *target, int len);

void print_request_header(http_request_t *h_req);

#endif
