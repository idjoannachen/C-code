#include <stdio.h>
#include <math.h>

#define COUNT_COLS 5
#define COUNT_ROWS 3

void PrintMatrix (int matrix1[][COUNT_COLS], int rows, int cols);	
int Sumrow (int matrix1[][COUNT_COLS], int row, int cols);
int Sumcolumn (int matrix1[][COUNT_COLS], int rows, int col);
int Summatrix (int matrix1[][COUNT_COLS], int rows, int cols);


int main (void){
	
	int MyMatrix[COUNT_ROWS][COUNT_COLS] = {{1, 2, 3, 4, 5}, {2, 4, 6, 8, 10}, {3, 6, 9, 12, 15}};

	PrintMatrix (MyMatrix, COUNT_ROWS, COUNT_COLS); //run the function for print matrix
	printf("The sum of row 0 is: %d\n", Sumrow(MyMatrix, 0, COUNT_COLS)); //run the function for print result of sum of row
	printf("The sum of row 1 is: %d\n", Sumrow(MyMatrix, 1, COUNT_COLS)); //run the function for print result of sum of row
	printf("The sum of row 2 is: %d\n", Sumrow(MyMatrix, 2, COUNT_COLS)); //run the function for print result of sum of row
	
	printf("The sum of column 0 is: %d\n", Sumcolumn(MyMatrix, COUNT_ROWS, 0)); //run the function for print result of sum of column
	printf("The sum of column 1 is: %d\n", Sumcolumn(MyMatrix, COUNT_ROWS, 1)); //run the function for print result of sum of column
	printf("The sum of column 2 is: %d\n", Sumcolumn(MyMatrix, COUNT_ROWS, 2)); //run the function for print result of sum of column
	printf("The sum of column 3 is: %d\n", Sumcolumn(MyMatrix, COUNT_ROWS, 3)); //run the function for print result of sum of column
	printf("The sum of column 4 is: %d\n", Sumcolumn(MyMatrix, COUNT_ROWS, 4)); //run the function for print result of sum of column
	
	printf("The sum of matrix is: %d\n", Summatrix(MyMatrix, COUNT_ROWS, COUNT_COLS)); //run the function for print result of sum of all matrix
	return 0;
}
// function of print matrix
void PrintMatrix (int matrix1[][COUNT_COLS], int rows, int cols){
	int i=0,j=0;

	for (i=0; i<rows; i++){	
		for (j=0; j<cols; j++){	
			printf("%d ", matrix1[i][j]);	
											
		}
		printf("\n");
	}
	
}
// function of find sum of row
int Sumrow (int matrix1[][COUNT_COLS], int row, int cols){
	int j=0, sum = 0;
	for (j=0; j<cols; j++){	
		sum += matrix1[row][j];
	}
	return sum;
}
// function of find sum of column
int Sumcolumn (int matrix1[][COUNT_COLS], int rows, int col){
	int j=0, sum = 0;
	for (j=0; j<rows; j++){	
		sum += matrix1[j][col];
	}
	return sum;
}
// function of find sum of matrix
int Summatrix (int matrix1[][COUNT_COLS], int rows, int cols){
	int i = 0; int j=0, sum = 0;
	for (i=0; i<rows; i++)
	for (j=0; j<cols; j++){	
		sum += matrix1[i][j];
	}
	return sum;
}