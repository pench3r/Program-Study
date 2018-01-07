#include "numethod.h"

int main(int argc, char *argv[]) {
	Fract2Array result_array;
	double fac_array[ROW][COL] = { {2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
	double con_array[ROW] = {8, -11, 3};
	Fract2ArrayInit(&result_array);
	ShowFract2Array(&result_array);
	return 0;
}
