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

void test_parse_null() {
	lj_value value;
	value.type = LJ_FALSE;
	EXPECT_EQ_INT(LJ_PARSE_OK, lj_parse(&value, "null"));
	EXPECT_EQ_INT(LJ_NULL, lj_get_type(&value));
}

void test_parse() {
	EXPECT_EQ_INT(1, 2);	
	EXPECT_EQ_INT(2, 2);	
	EXPECT_EQ_INT(3, 2);	
	EXPECT_EQ_INT(3, 3);	
}

int main(int argc, char *argv[]) {
	test_parse_null();
	printf("test: %d/%d,  (%3.2f%%) passed\n", test_pass, test_count, test_pass*100.0 / test_count);	
	return 0;
}
