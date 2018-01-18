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

#define TEST_PARSE_BASIC(parse_result, literal_str, literal_type) \
	do {\
		lj_value value;\
		value.type = LJ_FALSE;\
		EXPECT_EQ_INT(parse_result, lj_parse(&value, literal_str));\
		EXPECT_EQ_INT(literal_type, lj_get_type(&value));\
	} while(0) 

static void test_parse_null() {
	TEST_PARSE_BASIC(LJ_PARSE_OK, "null", LJ_NULL);
}

static void test_parse_true() {
	TEST_PARSE_BASIC(LJ_PARSE_OK, "true", LJ_TRUE);
}

static void test_parse_false() {
	TEST_PARSE_BASIC(LJ_PARSE_OK, "false", LJ_FALSE);
}

static void test_parse_expect_value() {
	TEST_PARSE_BASIC(LJ_PARSE_EXPECT_VALUE, "", LJ_NULL);
	TEST_PARSE_BASIC(LJ_PARSE_EXPECT_VALUE, " ", LJ_NULL);
}

static void test_parse_invalid_value(){
	TEST_PARSE_BASIC(LJ_PARSE_INVALID_VALUE, "nul", LJ_NULL);
	TEST_PARSE_BASIC(LJ_PARSE_INVALID_VALUE, "?", LJ_NULL);
}

static void test_parse_root_not_singular() {
	TEST_PARSE_BASIC(LJ_PARSE_ROOT_NOT_SINGULAR, "null x", LJ_NULL);
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
