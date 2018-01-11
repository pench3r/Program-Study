#include "ljson.h"

// define ljson parse func
int lj_parse(lj_value *v, const char *json) {
	return 1;
}

// define ljson get type func
lj_type lj_get_type(const lj_value *v) {
	return LJ_TRUE;
}
