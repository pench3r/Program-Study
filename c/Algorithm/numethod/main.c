#include "numethod.h"

int main(int argc, char *argv[]) {
	Fract2Array result_array, con_fac_array;
	double fac_array[ROW][COL] = { {2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
	double con_array[ROW] = {8, -11, 3};
	Fract2ArrayInit(&result_array);
	ShowFract2Array(&result_array);
	DoubleaToFracta2(fac_array, con_fac_array);
	ShowFract2Array(&con_fac_array);
	Fract f1 = {1, 12};
	Fract f2 = {2, 16};
	Fract result = FractAdd(f1, f2);
	Fract result1 = FractMul(f1, f2);
	PrintFract(result);
	PrintFract(result1);
	int retval = CommonDivisor(30, 15);
	printf("The data is %d.\n", retval);
	return 0;
}
