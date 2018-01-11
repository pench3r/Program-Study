#include "ljson.h"

int main(int argc, char *argv[]) {
	lj_value value_t;
	char json[] = "This is test";
	lj_parse(&value_t, json);
	int retval = lj_get_type(&value_t); 
	printf("The result is %d.\n", retval);	
	return 0;
}
