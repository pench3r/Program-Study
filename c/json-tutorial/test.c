#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ljson.h"

static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do {\
		test_count++;\
		if (equality)\
			test_pass++;\
		else {\
			fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
		}\
	} while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE(((expect) == (actual)), expect, actual, "%d ")

static void test_parse_null() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_OK, lj_parse(&value, "null"));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));
}

static void test_parse_true() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_OK, lj_parse(&value, "true"));
	EXPECT_EQ_INT(LJ_TRUE, lj_get_type(&value));
}

static void test_parse_false() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_OK, lj_parse(&value, "false"));
	EXPECT_EQ_INT(LJ_FALSE, lj_get_type(&value));
}

static void test_parse_expect_value() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_EXPECT_VALUE, lj_parse(&value, ""));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));

	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_EXPECT_VALUE, lj_parse(&value, " "));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));
}

static void test_parse_invalid_value(){
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_INVALID_VALUE, lj_parse(&value, "nul"));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));

	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_INVALID_VALUE, lj_parse(&value, "?"));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));
}

static void test_parse_root_not_singular() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_ROOT_NOT_SINGULAR, lj_parse(&value, "null x"));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));
}

static void test_parse() {
	test_parse_null();
	test_parse_expect_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
	test_parse_true();
	test_parse_false();
}

int main(int argc, char *argv[]) {
	test_parse();
	printf("test: %d/%d,  (%3.2f%%) passed\n", test_pass, test_count, test_pass*100.0 / test_count);	
	return 0;
}
