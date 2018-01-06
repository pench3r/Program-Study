#include "numethod.h"

int main(int argc, char *argv[]) {
	ResultArray result_array;
	result_array[0] = 1.0;
	result_array[1] = 2.0;
	result_array[2] = 3.0;
	double fac_array[ROW][COL] = { {2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
	double con_array[ROW] = {8, -11, 3};
	Gauss(fac_array, con_array, &result_array);
	ShowResultArray(&result_array, ROW);
	return 0;
}
