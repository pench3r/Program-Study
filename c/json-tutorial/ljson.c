#include "ljson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL, strtod() */
#include <stdio.h>

// define ljson parse func
lj_parse_result lj_parse(lj_value *v, const char *json) {
	lj_context context;
	context.json = json;
	v->type = LJ_NULL;
	lj_parse_whitespace(&context);
	return lj_parse_value(&context, v);	
}

// define ljson parse literal func
lj_parse_result lj_parse_literal(lj_context *context, lj_value *v, const char *literal_str, lj_type literal_type) {
	int literal_str_len = 0;
	const char *tmp_str = literal_str;
	while (*tmp_str != '\0') {
		tmp_str++;
		literal_str_len++;
	}
	for (int str_index=0; str_index < literal_str_len+1; ++str_index) {
		if (*(context->json+str_index) != *(literal_str+str_index)) return LJ_PARSE_INVALID_VALUE;
	}
	v->type = literal_type;
	return LJ_PARSE_OK;
}

// define ljson parse null func
lj_parse_result lj_parse_null(lj_context *context, lj_value *v) {
	if (context->json[0] != 'n' || context->json[1] != 'u' || context->json[2] != 'l' || context->json[3] != 'l' || context->json[4] != '\0') return LJ_PARSE_INVALID_VALUE;
	v->type = LJ_NULL;
	return LJ_PARSE_OK;
}

// define ljson parse true func
lj_parse_result lj_parse_true(lj_context *context, lj_value *v) {
	if (context->json[0] != 't' || context->json[1] != 'r' || context->json[2] != 'u' || context->json[3] != 'e' || context->json[4] != '\0') return LJ_PARSE_INVALID_VALUE;
	v->type = LJ_TRUE;
	return LJ_PARSE_OK;
}

// define ljson parse false func
lj_parse_result lj_parse_false(lj_context *context, lj_value *v) {
	if (context->json[0] != 'f' || context->json[1] != 'a' || context->json[2] != 'l' || context->json[3] != 's' || context->json[4] != 'e' || context->json[5] != '\0') return LJ_PARSE_INVALID_VALUE;
	v->type = LJ_FALSE;
	return LJ_PARSE_OK;
} 

// define ljson parse number func
lj_parse_result lj_parse_number(lj_context *context, lj_value *value) {
	const char *tmp_json = context->json;
	/* negative */
	if (*tmp_json == '-') tmp_json++;
	/* int */
	if (*tmp_json == '0') {
		tmp_json++;
		if (*tmp_json != '\0' && *tmp_json != '.') return LJ_PARSE_ROOT_NOT_SINGULAR;			
	} 
	else {
		/* not 1-9 */
		if (*tmp_json < 0x31 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
		/* skip 0-9 */
		while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
			tmp_json++;
	}
	/* fract */
	if (*tmp_json == '.') {
		tmp_json++;
		if (*tmp_json < 0x30 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
		while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
			tmp_json++;
	}
	/* indexs */
	if (*tmp_json == 'e' || *tmp_json == 'E') {
		tmp_json++;
		if (*tmp_json == '+' || *tmp_json == '-') tmp_json++;
		if (*tmp_json < 0x30 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
		while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
			tmp_json++;
	}
	char *end;
	value->lj_number = strtod(context->json, &end);
	if (context->json == end) return LJ_PARSE_INVALID_VALUE;
	value->type = LJ_NUMBER;
	return LJ_PARSE_OK;
}

// define ljson parse number func personal version
lj_parse_result lj_parse_number_m(lj_context *context, lj_value *value) {
	const char *tmp_json = context->json;
	char *final_json;
	if (*tmp_json != '-' && (*tmp_json < 0x30 || *tmp_json > 0x39)) return LJ_PARSE_INVALID_VALUE;
	if (*tmp_json == '-') tmp_json++;
	if (*tmp_json == '0' && *(tmp_json+1) == '\0') {
		value->lj_number = 0.0;
		value->type = LJ_NUMBER;
		return LJ_PARSE_OK;		
	}
	if (*tmp_json == '0' && *(tmp_json+1) == '.' && *(tmp_json+2) == '0') {
		value->lj_number = 0.0;
		value->type = LJ_NUMBER;
		return LJ_PARSE_OK;	
	}
	if (*tmp_json == '0' && *(tmp_json+1) != '\0') return LJ_PARSE_ROOT_NOT_SINGULAR;		
	if (*tmp_json < 0x30 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
	while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
		tmp_json++;
	if (*tmp_json == '\0') {
		value->lj_number = strtod(context->json, &final_json);
		value->type = LJ_NUMBER;
		return LJ_PARSE_OK;
	}
	if (*tmp_json == '.') { 
		tmp_json++;
		if (*tmp_json < 0x30 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
		while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
			tmp_json++;
		if (*tmp_json == '\0') {
			value->lj_number = strtod(context->json, &final_json);
			value->type = LJ_NUMBER;
			return LJ_PARSE_OK;
		}
	}
	if (*tmp_json != 'e' && *tmp_json != 'E') return LJ_PARSE_INVALID_VALUE;
	tmp_json++;
	if (*tmp_json == '-' || *tmp_json == '+') tmp_json++;		
	if (*tmp_json < 0x30 || *tmp_json > 0x39) return LJ_PARSE_INVALID_VALUE;
	while (*tmp_json >= 0x30 && *tmp_json <= 0x39)
		tmp_json++;
	if (*tmp_json == '\0') {
		value->lj_number = strtod(context->json, &final_json);
		value->type = LJ_NUMBER;
		return LJ_PARSE_OK;
	}
	return LJ_PARSE_INVALID_VALUE;
}

// define ljson parse value func
int lj_parse_value(lj_context *context, lj_value *v) {
	const char *tmp_json = context->json;
	while ( *tmp_json != ' ' && *tmp_json != '\t' && *tmp_json != '\r' && *tmp_json != '\n' && *tmp_json != '\0')
		tmp_json++;
	while ( *tmp_json == ' ' || *tmp_json == '\t' || *tmp_json == '\r' || *tmp_json == '\n')	
		tmp_json++;
	if ( *tmp_json != '\0') return LJ_PARSE_ROOT_NOT_SINGULAR;
	switch(*context->json) {
		case 'f': return lj_parse_literal(context, v, "false", LJ_FALSE);
		case 'n': return lj_parse_literal(context, v, "null", LJ_NULL);
		case 't': return lj_parse_literal(context, v, "true", LJ_TRUE);
		case '\0': return LJ_PARSE_EXPECT_VALUE;
		default: return lj_parse_number(context, v);
	}
}

// define ljson trim whitespace func
void lj_parse_whitespace(lj_context *context) {
	const char *tmp = context->json;
	while ( *tmp == ' ' || *tmp == '\t' || *tmp == '\r' || *tmp == '\n')	
		tmp++;
	context->json = tmp;
}

// define ljson get type func
lj_type lj_get_type(const lj_value *v) {
	return v->type;
}

// define ljson get lj_number func
double lj_get_number(const lj_value *v) {
	assert(v->type == LJ_NUMBER);
	return v->lj_number;
}
