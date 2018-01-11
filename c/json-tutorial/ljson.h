#ifndef LJSON_H__
#define LJSON_H__

typedef enum { LJ_NULL, LJ_FALSE, LJ_TRUE, LJ_NUMBER, LJ_ARRAY, LJ_OBJECT} lj_type;

enum {
	LJ_PARSE_OK = 0,
	LJ_PARSE_EXCEPT_VALUE,
	LJ_PARSE_INVALID_VALUE,
	LJ_PARSE_ROOT_NOT_SINGULAR
};

typedef struct _lj_value {
	lj_type type;
} lj_value;

/* struct json parse func */
int lj_parse(lj_value *v, const char *json);

/* struct json get type func */
lj_type lj_get_type(const lj_value *v);

#endif /* LJSON_H__ */
