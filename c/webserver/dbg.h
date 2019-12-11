#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define expr_is_false_log_it(A, M, ...) if(!(A)){log_err(M, ##__VA_ARGS__);}

#define expr_is_false_log_it_and_exit(A, M, ...) if(!(A)){log_err(M, ##__VA_ARGS__);exit(-1);} 


#endif
