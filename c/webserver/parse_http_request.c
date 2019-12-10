#include "parse_http_request.h"


int orgstr1_compare_tarstr2_with_fix_len(void *start, void *target, int len) {
	for (int i = 0; i<len; ++i) {
		if (*(char *)(start+i) != *(char *)(target+i))
			return -1;
	}
	return 0;
}


void send_content(int fd, char *content, int content_len) {
  int send_bytes = 10;
  int round = content_len / send_bytes;
  int reminder = content_len % send_bytes;
  if (reminder != 0) {
    round++;
  }
  char *send_buf = content;
  while (round > 0) {
    if (round == 1) {
      send_bytes = reminder;
    }
    send(fd, send_buf, send_bytes, 0);
    send_buf += send_bytes;
    round--;
  }
}


void print_request_header(http_request_t *req) {
	request_header_t *header;
	printf("header num: %d\n", req->header_num);
	for (int i=0; i<req->header_num; ++i) {
		header = req->headers[i];
		printf("header %.*s: %.*s\n", header->rh_key_len, (char *)header->rh_key, header->rh_val_len, (char *)header->rh_val);
	}

}


void build_response_and_out_to_socket(http_response_t *h_rsp) {
    char resp_header[1024];
		int cfd = h_rsp->fd;
    if (h_rsp->rsp_file_addr == NULL) {
      sprintf(resp_header, "HTTP/1.1 %d %s\n", 404, "Not Found");
      sprintf(resp_header, "%sContent-Type: text/html; charset=UTF-8\n", resp_header);
      sprintf(resp_header, "%sServer: za\n\n", resp_header);
          
      send_content(cfd, resp_header, strlen(resp_header));
    } else {
      sprintf(resp_header, "HTTP/1.1 %d %s\n", 200, "OK");
      sprintf(resp_header, "%sContent-Type: text/html; charset=UTF-8\n", resp_header);
      sprintf(resp_header, "%sServer: za\n", resp_header);
      sprintf(resp_header, "%sContent-Length: %d\n\n", resp_header, h_rsp->rsp_file_size);
      send_content(cfd, resp_header, strlen(resp_header));
			send_content(cfd, h_rsp->rsp_file_addr, h_rsp->rsp_file_size);
    }

}


http_request_t* new_http_request_t(int fd, int epfd) {
  http_request_t *new_hreq = (http_request_t *)malloc(sizeof(http_request_t));
  new_hreq->fd = fd;
  new_hreq->epfd = epfd;
  new_hreq->state = 0;
  new_hreq->recv_bytes = 0;
  new_hreq->start = 0;
  new_hreq->end = 0;
	new_hreq->header_num = 0;
  // for (int i = 0; i<sizeof(new_hrt->request)/sizeof(new_hrt->request[0]); ++i) {
  //  new_hrt->request[i] = '0';
  // }
	return new_hreq;
}


http_response_t* new_http_response_t(int fd) {
	http_response_t *new_hrsp = (http_response_t *)malloc(sizeof(http_response_t));
	new_hrsp->fd = fd;
	new_hrsp->rsp_file_addr = NULL;
	new_hrsp->status_code = 404;
	new_hrsp->rsp_file_size = 0;
	return new_hrsp;
}


void destory_http_response_t(http_response_t* hrsp) {
	if (hrsp->rsp_file_addr != NULL) {
		if (munmap(hrsp->rsp_file_addr, (size_t)hrsp->rsp_file_size) == -1) {
			perror("ummap error");
		}	
	}
	free(hrsp);
}


int parse_http_request(http_request_t *h_req) {
  if (parse_http_request_first_line(h_req) != HP_PARSE_OK) {
		return HP_PARSE_ERR;
  }
  if (parse_http_request_header(h_req) != HP_PARSE_OK) {
    // print_request_header(c_http_request);
		return HP_PARSE_ERR;
  }	
	return HP_PARSE_OK;
}


int parse_http_request_first_line(http_request_t *h_req) {
	enum {
		hp_start = 0,
		hp_method,
		hp_uri,
		hp_http,
		hp_http_major_version,
		hp_http_minor_version,
		hp_done
	} state;
	state = h_req->state;
	char *request = h_req->request_buf;
	int start = h_req->start;
	char ch;
	char *cur_pos;
	for (int end = h_req->end; end<h_req->recv_bytes; ++end) {
		cur_pos = request + end;
		ch = *cur_pos;
		switch(state) {
			case hp_start:
				if (ch < 'A' || ch > 'Z')
					return HP_PARSE_ERR;	
				state = hp_method;
				break;
			case hp_method:
				if ((ch > 'A' && ch < 'Z') || ch == ' ')
					break;
				if (ch == '/') {
					if ((end-start) == 4) {
						if (orgstr1_compare_tarstr2_with_fix_len(request+start, "GET ", 4) == 0) {
							// GET METHOD
							state = hp_uri;
							start = end;
							break;	
						}
					}
					if ((end-start) == 5) {
						printf("POST proc\n");
						if (orgstr1_compare_tarstr2_with_fix_len(request+start, "POST ", 5) == 0) {
							// POST METHOD
							state = hp_uri;
							start = end;
							break;
						}
					}
				}
				return HP_PARSE_ERR;
			case hp_uri:
				if (ch == ' ') {
					h_req->rq_uri = request + start;	
					h_req->rq_uri_len = end - start;
					// save uri start and uri stop
					state = hp_http;
					start = end;
				}
				break;
			case hp_http:
				if (ch > 'A' && ch < 'Z')
					break;
				if (ch == '/') {
					// check HTTP
					state = hp_http_major_version;
					break;
				}
				return HP_PARSE_ERR;
			case hp_http_major_version:
				if (ch == '.') {
					state = hp_http_minor_version;
				}
				break;
			case hp_http_minor_version:
				if (ch > '0' && ch < '2')
					break;
				if (ch == '\n') {
					start = end;
					h_req->start = start + 1;
					h_req->end = end + 1;
					h_req->state = 0;
					return HP_PARSE_OK;
				}
				return HP_PARSE_ERR;
			default:
				return HP_PARSE_ERR;
		}	
	}
	return HP_PARSE_ERR;
}


int parse_http_request_header(http_request_t *h_req) {
	enum {
		rq_start = 0,
		rq_header,
		rq_colon,
		rq_space,
		rq_value,
		rq_value_done
	}	state;
	state = h_req->state;
	char ch;
	char *cur_pos; 
	char *header_key;
	char *header_val;
	int header_key_len;
	int header_val_len;
	char *request = h_req->request_buf;
	int start = h_req->start;
	for (int end=h_req->end; end<h_req->recv_bytes; ++end) {
		cur_pos = request + end;
		ch = *cur_pos;
		switch(state) {
			case rq_start:
				if (ch > 'A' && ch < 'Z'){
					state = rq_header;
					break;	
				}
				return HP_PARSE_ERR;
			case rq_header:
				if ((ch > 'A' && ch < 'Z') || (ch > 'a' && ch < 'z') || ch == '-')
					break;
				if (ch == ':') {
					header_key = request + start;
					header_key_len = end - start;
					state = rq_colon;
					break;
				}
				return HP_PARSE_ERR;
			case rq_colon:
				if (ch == ' ') {
					state = rq_space;
					break;
				}
				return HP_PARSE_ERR;
			case rq_space:
				if ((ch > 'A' && ch < 'Z') || (ch >'a' && ch < 'z')) {
					start = end;
					state = rq_value;
					break;
				}
				return HP_PARSE_ERR;
			case rq_value:
				if (ch != '\n')
					break;
				header_val = request + start;
				header_val_len = end - start;
				request_header_t *header = (request_header_t *)malloc(sizeof(request_header_t));
				header->rh_key = header_key;
				header->rh_key_len = header_key_len;
				header->rh_val = header_val;
				header->rh_val_len = header_val_len;
				if (h_req->header_num < MAX_HEADER_NUM-1) {
					h_req->headers[h_req->header_num] = header;
					h_req->header_num++;
				}
				state = rq_value_done;
				break;
			case rq_value_done:
				if (ch > 'A' && ch < 'Z'){
					start = end;
					state = rq_header;
					break;	
				}
				if (ch == '\n')
					return HP_PARSE_OK;
				return HP_PARSE_ERR;
		}
	}
	return HP_PARSE_ERR;
}

// int main(int argc, char *argv[]) {
// 	request_t rt;
// 	rt.state = 0;
// 	rt.start = 0;
// 	rt.end = 0;
// 	rt.header_num = 0;
// 	char *t = "GET /sss HTTP/1.1\nHost: ssss\nCookie: s1ssContent-Types: bb2\nServer: Nginx3\n\n";
// 	rt.recv_bytes = strlen(t);
// 	if (http_parse_request_first_line(&rt,t) == HP_PARSE_OK) {
// 		printf("first\n");
// 	}
// 	printf("uri: %.*s\n", rt.rq_uri_len, (char *)rt.rq_uri);
// 	if (http_parse_request_header(&rt, t) == HP_PARSE_OK) {
// 		printf("HEEEADER\n");
// 	}
// 	
// 	return 0;
// }
