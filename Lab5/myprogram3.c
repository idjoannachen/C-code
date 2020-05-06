#include <stdio.h>
#include <math.h>
#define SENTINEL 1000

int main (void){
	int n;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int f = 0;
	double e = 0.0;
	printf("Enter number");
	scanf("%d", &n);
	while (n != SENTINEL) {
		if (n>=85){
			printf("It's a hot day\n");
			a += 1;
			d += n;
		}
		else if (60<=n&&n<=84) {
			b += 1;
			d += n;
			printf("It's a pleasant day\n");
		}
		else {
			printf("It's a cold day\n");
			c += 1;
			d += n;
		}
		//scan a new number
		printf("Enter number or 1000 to end\n");/
		scanf("%d", &n);
	}
	printf("There are %d hot days, %d pleasant days, and %d cold days.\n", a, b, c);
	e = d/(a+b+c);
	printf("The average temperature is %.3lf.\n", e);
	return 0;
}