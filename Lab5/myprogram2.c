#include <stdio.h>
#include <math.h>

int main(){
	char a;				
	int nextNumber;
	int b = 0;
	
	printf("Enter the integer number");
	a = getchar(); //take the first integer
	
	while (a <= '9' && a >= '0'){
		nextNumber = (int)a - (int)'0';
		printf("%d\n",nextNumber);
		a = getchar();
		b += nextNumber;
	}
	
	if (b%9 ==0)
		printf("This number is divisible by 9.");
	else 
		printf("This number is not divisible by 9.");
	return 0;
}