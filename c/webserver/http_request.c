#include "http_request.h"
#include <stdlib.h>

http_request_t* new_http_request_t(int fd, int epfd) {
	http_request_t *new_hrt = (http_request_t *)malloc(sizeof(http_request_t));
	new_hrt->fd = fd;
	new_hrt->epfd = epfd;
	new_hrt->state = 0;
	new_hrt->recv_total_bytes = 0;
	new_hrt->start = 0;
	new_hrt->end = 0;
	// for (int i = 0; i<sizeof(new_hrt->request)/sizeof(new_hrt->request[0]); ++i) {
	// 	new_hrt->request[i] = '0';
	// }
}
