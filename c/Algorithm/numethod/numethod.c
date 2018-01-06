#include "numethod.h"

// define Show array func
void ShowArray(double array[3][3]) {
	printf("show array info:\n");
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j) {
			printf("%f ", array[i][j]);
		}
		printf("\n");
	}
}

// define Show result array func
void ShowResultArray(ResultArray *array, int size) {
	printf("%f", (*array)[0]);
	for (int i=0; i<size; ++i) {
		printf("%f ", (*array)[i]);
	}	
	printf("\n");
}

// define Print Fract func
void PrintFract(Fract *fract) {
	printf("%d/%d", fract->num, fract->deno);
}

// define Gauss func
void Gauss(double fac_array[ROW][COL], double con_array[ROW], double (*result_array)[ROW]) {
	// find max abs(value) in first col, row = 1 	
// 	while(row < ROW && col < COL) {
// 		row = 0
// 		max_row = 0;
// 		col = 0
// 		for (int i=row+1; i<ROW; ++i) {
// 			if (abs(fac_array[i][col]) > abs(fac_array[max_row][col])) {
// 				max_row = i;
// 			}	
// 		}
// 		ArrayRowSwitch(fac_array[row], fac_array[max_row]);
// 		ArrayRowSwitch(con_array[row], con_array[max_row]);
// 	
// 		// row+1 to ROW , per row add x*(row) to specify per row[col] is zero
// 		for (int i=row+1; i<ROW; ++i) {
// 			int x = -(fac_array[i][col] / fac_array[row][col]);
// 			for (int j=0; j<COL; ++j) {
// 				fac_array[i][j] = x * fac_array[row][j] + fac_array[i][j];
// 			}
// 			con_array[i] = x * con_array[row] + con_array[i];
// 		}
// 		row++;
// 		col++;
//	}
	// acquire final result
	(*result_array)[0] = 16;
	return;
}
