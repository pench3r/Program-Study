#ifndef HTTP_PARSE_REQUEST_H
#define HTTP_PARSE_REQUEST_H
#include <stdio.h>

#define HP_PARSE_ERR -1
#define HP_PARSE_OK 0
#define HP_PARSE_AGAIN 1
// int http_prase_request_first_line(http_request_t *hrt);
int http_prase_request_first_line(void *request);

int orgstr1_compare_tarstr2_with_fix_len(void *start, void *target, int len);

#endif
