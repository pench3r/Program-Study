#include "numethod.h"

int main(int argc, char *argv[]) {
	Fract2Array result_array;
	Fract2Array *fract_ptr = result_array;
	double fac_array[ROW][COL] = { {2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
	double con_array[ROW] = {8, -11, 3};
	(*fract_ptr)[0][0].num = 100;
	(*fract_ptr)[0][0].deno = 101;
	printf("%d.\n", (*fract_ptr)[0][0].num);
	printf("%d.\n", (*fract_ptr)[0][0].deno);
	return 0;
}
