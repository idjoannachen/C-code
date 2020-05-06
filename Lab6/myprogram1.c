#include <stdio.h>
#include <math.h>

void bills(int number, int *fifty, int *twenty, int *ten);
int main(int argc, char *argv[]) {
    int number = 0; 
	int fifty = 0; 
	int twenty = 0; 
	int ten =0;
	
	printf("\n Enter the amount you want, it has to be a multiple of 10: ");
	scanf("%d", &number);
	bills(number, &fifty, &twenty, &ten);
}

void bills(int number, int *fifty, int *twenty, int *ten){
	*fifty = number/50;
	*twenty = number%50/20;
	*ten = number%50%20/10;
	printf("\n I will give you %d fifty doller, %d twenty doller, %d ten doller.", *fifty, *twenty, *ten);
}