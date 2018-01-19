#ifndef LJSON_H__
#define LJSON_H__

typedef enum { LJ_NULL, LJ_FALSE, LJ_TRUE, LJ_NUMBER, LJ_ARRAY, LJ_OBJECT} lj_type;

typedef enum {
	LJ_PARSE_OK = 0,
	LJ_PARSE_EXPECT_VALUE,
	LJ_PARSE_INVALID_VALUE,
	LJ_PARSE_ROOT_NOT_SINGULAR
} lj_parse_result;

typedef struct _lj_value {
	double lj_number;
	lj_type type;
} lj_value;

typedef struct _lj_context {
	const char *json;
} lj_context;

/* struct json parse func
   return parse result 
*/
lj_parse_result lj_parse(lj_value *v, const char *json);

/* struct json get type func */
lj_type lj_get_type(const lj_value *v);

/* struct json get number if exists func */
double lj_get_number(const lj_value *v);

/* struct json get value func */
int lj_parse_value(lj_context *context, lj_value *value);

/* struct json trim whitespace */
void lj_parse_whitespace(lj_context *context);

/* struct json null type parse func */
lj_parse_result lj_parse_null(lj_context *context, lj_value *value);

/* struct json true type parse func */
lj_parse_result lj_parse_true(lj_context *context, lj_value *value);

/* struct json false type parse func */
lj_parse_result lj_parse_false(lj_context *context, lj_value *value);

/* struct json literal parse func */
lj_parse_result lj_parse_literal(lj_context *context, lj_value *value, const char *literal_str, lj_type literal_type);

/* struct json number parse func */
lj_parse_result lj_parse_number(lj_context *context, lj_value *value);

#endif /* LJSON_H__ */
