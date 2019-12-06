#include "http_parse_request.h"


typedef struct request_t_ {
	int start;
	int end;
	int state;
	int recv_bytes;
} request_t;


int orgstr1_compare_tarstr2_with_fix_len(void *start, void *target, int len) {
	for (int i = 0; i<len; ++i) {
		if (*(char *)(start+i) != *(char *)(target+i))
			return -1;
	}
	return 0;
}


int http_parse_request_first_line(request_t *rt, void *request) {
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
	char ch;
	int start = rt->start;
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
		end++;
	}
	rt->start = 0;
	rt->end = 0;
	rt->state = state;
	return HP_PARSE_AGAIN;
}


int http_parse_request_header(request_t *rt, void *request) {
	enum {
		start = 0,
		rq_header,
		rq_colon,
		rq_space,
		rq_value,
		rq_value_done
	}	state;
	state = rt->state;
	char ch;
	int end = rt->end;
	char *cur_pos; 
	while(1) {
		cur_pos = request + end;
		ch = *cur_pos;
		switch(state) {
			case start:
				if (ch > 'A' && ch < 'Z'){
					state = rq_header;
					break;	
				}
				return HP_PARSE_ERR;
			case rq_header:
				if ((ch > 'A' && ch < 'Z') || (ch > 'a' && ch < 'z') || ch == '-')
					break;
				if (ch == ':') {
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
					state = rq_value;
					break;
				}
				return HP_PARSE_ERR;
			case rq_value:
				if (ch != '\n')
					break;
				state = rq_value_done;
				break;
			case rq_value_done:
				if (ch > 'A' && ch < 'Z'){
					state = rq_header;
					break;	
				}
				if (ch == '\n')
					return HP_PARSE_OK;
				return HP_PARSE_ERR;
		}
		end++;
	}
	rt->start = 0;
	rt->end = 0;
	rt->state = state;	
	return HP_PARSE_AGAIN;
}

int main(int argc, char *argv[]) {
	request_t rt;
	rt.state = 0;
	rt.start = 0;
	rt.end = 0;
	char *t = "GET/sss HTTP/1.1\nContent-Type: sxsSS: bb\n";
	rt.recv_bytes = strlen(t);
	if (http_parse_request_first_line(&rt,t) == HP_PARSE_OK) {
		printf("first\n");
	}
	if (http_parse_request_header(&rt, t) == HP_PARSE_OK)
		printf("HEEEADER\n");
	return 0;
}
