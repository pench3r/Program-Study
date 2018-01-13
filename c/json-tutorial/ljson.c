#include "ljson.h"

// define ljson parse func
int lj_parse(lj_value *v, const char *json) {
	lj_context context;
	context.json = json;
	return lj_parse_value(&context, v);	
}

// define ljson parse value func
int lj_parse_value(lj_context *context, lj_value *v) {
	if (context->json[0] != 'n' || context->json[1] != 'u' || context->json[2] != 'l' || context->json[3] != 'l' || context->json[4] != '\0') return LJ_PARSE_INVALID_VALUE;
	v->type = LJ_NULL;
	return LJ_PARSE_OK;
}

// define ljson get type func
lj_type lj_get_type(const lj_value *v) {
	return v->type;
}
