#include <stdio.h>
#include <string.h>
#include <math.h>

void scan_data(char *operator, double *operand);
void do_next_op(char operator, double operand, double *result);
int main(){
    double result = 0.0;
	char operator;
	double operand;
	
	do{
		printf("The result is %.3lf.\n", result);
		scan_data(&operator, &operand);
		do_next_op(operator, operand, &result);
		
	}
	while(operator!='q');
	return 0;
}

void scan_data(char *operator, double *operand){
	char d;
	scanf("%c %lf", operator, operand);
	scanf("%c", &d);
	fflush(stdin);
}

void do_next_op(char operator, double operand, double *result){
	int i =0;
	switch(operator){
		case '+':
		*result += operand;
		break;
		case '-':
		*result -= operand;
		break;
		case '*':
		*result *= operand;
		break;
		case '/':
		*result /= operand;
		break;
		case '^':
		*result = pow(*result, operand);
		break;
	}
}
	