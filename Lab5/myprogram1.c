#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int times = 0;
	int number = 0;
	int x = 0; 
	
	printf("\nEnter an digit number integer: ");
	scanf("%d", &number);
	
	while (number > 0) {
		x = x + number % 10;
    	number = number / 10;
	}
	
	if (x % 9 == 0)
		printf("\nThis number is divisible by 9 ");
	else 
		printf("\nThis number is not divisible by 9 ");
}
