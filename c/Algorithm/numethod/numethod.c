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

// define show fract2array func
void ShowFract2Array(Fract2Array *array) {
	for (int i=0; i<ROW; ++i) {
		for (int j=0; j<COL; ++j) {
			PrintFract((*array)[i][j]);
		}
		printf("\n");
	}
} 

// define Print Fract func
void PrintFract(Fract fract) {
	assert(fract.deno != 0);	
	if (fract.num % fract.deno == 0) {
		printf("%d ", fract.num/fract.deno);
		return;
	}
	printf("%d/%d ", fract.num, fract.deno);
}

// define Fract2array init func
void Fract2ArrayInit(Fract2Array *array) {
	for (int i=0; i<ROW; ++i) {
		for (int j=0; j<COL; ++j) {
			(*array)[i][j].num = i;
			(*array)[i][j].deno = i+1;
		}
	}
}

// define Intarray to Fractarray func
Fract *DoubleaToFracta(double array[ROW][COL]) {
	return NULL;
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
	return;
}
