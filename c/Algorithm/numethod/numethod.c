#include "numethod.h"

// define Show array func
void ShowArray(double array[3][2]) {
	for (int i=0; i<3; ++i) {
		for (int j=0; j<2; ++j) {
			printf("The data is %f.\n", array[i][j]);
		}
	}
}

// define Gauss func
void Gauss(double fac_array[ROW][COL], double con_array[ROW]) {
	// find max abs(value) in first col, row = 1 	
	while(row < ROW && col < COL) {
		row = 0
		max_row = 0;
		col = 0
		for (int i=row+1; i<ROW; ++i) {
			if (abs(fac_array[i][col]) > abs(fac_array[max_row][col])) {
				max_row = i;
			}	
		}
		ArrayRowSwitch(fac_array[row], fac_array[max_row]);
		ArrayRowSwitch(con_array[row], con_array[max_row]);
	
		// row+1 to ROW , per row add x*(row) to specify per row[col] is zero
		for (int i=row+1; i<ROW; ++i) {
			int x = -(fac_array[i][col] / fac_array[row][col]);
			for (int j=0; j<COL; ++j) {
				fac_array[i][j] = x * fac_array[row][j] + fac_array[i][j];
			}
			con_array[i] = x * con_array[row] + con_array[i];
		}
		row++;
		col++;
	}
	
	// acquire final result
	
}
