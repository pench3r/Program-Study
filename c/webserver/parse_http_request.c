#include "parse_http_request.h"


int orgstr1_compare_tarstr2_with_fix_len(void *start, void *target, int len) {
	for (int i = 0; i<len; ++i) {
		if (*(char *)(start+i) != *(char *)(target+i))
			return -1;
	}
	return 0;
}


void print_request_header(http_request_t *req) {
	request_header_t *header;
	printf("header num: %d\n", req->header_num);
	for (int i=0; i<req->header_num; ++i) {
		header = req->headers[i];
		printf("header %.*s: %.*s\n", header->rh_key_len, (char *)header->rh_key, header->rh_val_len, (char *)header->rh_val);
	}

}


http_request_t* new_http_request_t(int fd, int epfd) {
  http_request_t *new_hrt = (http_request_t *)malloc(sizeof(http_request_t));
  new_hrt->fd = fd;
  new_hrt->epfd = epfd;
  new_hrt->state = 0;
  new_hrt->recv_bytes = 0;
  new_hrt->start = 0;
  new_hrt->end = 0;
	new_hrt->header_num = 0;
  // for (int i = 0; i<sizeof(new_hrt->request)/sizeof(new_hrt->request[0]); ++i) {
  //  new_hrt->request[i] = '0';
  // }
}


int parse_uri(char *rq_uri, int rq_uri_len, char *filename) {
}


int parse_http_request_first_line(http_request_t *rt) {
	enum {
		hp_start = 0,
		hp_method,
		hp_uri,
		hp_http,
		hp_http_major_version,
		hp_http_minor_version,
		hp_done
	} state;
	state = rt->state;
	char *request = rt->request_buf;
	int start = rt->start;
	char ch;
	char *cur_pos;
	for (int end = rt->end; end<rt->recv_bytes; ++end) {
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
					rt->rq_uri = request + start;	
					rt->rq_uri_len = end - start;
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
					rt->start = start + 1;
					rt->end = end + 1;
					rt->state = 0;
					return HP_PARSE_OK;
				}
				return HP_PARSE_ERR;
			default:
				return HP_PARSE_ERR;
		}	
	}
	return HP_PARSE_ERR;
}


int parse_http_request_header(http_request_t *rt) {
	enum {
		rq_start = 0,
		rq_header,
		rq_colon,
		rq_space,
		rq_value,
		rq_value_done
	}	state;
	state = rt->state;
	char ch;
	char *cur_pos; 
	char *header_key;
	char *header_val;
	int header_key_len;
	int header_val_len;
	char *request = rt->request_buf;
	int start = rt->start;
	for (int end=rt->end; end<rt->recv_bytes; ++end) {
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
				if (rt->header_num < MAX_HEADER_NUM-1) {
					rt->headers[rt->header_num] = header;
					rt->header_num++;
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
