#include <stdio.h>
#include <string.h>
#include <math.h>
#define COUNT 10
#define COUNT_COLS 5
#define COUNT_ROWS 3

void print(int array[], int size);
int sum(int array[], int size);
void compare(int array1[], int array2[], int size);
int testsorted(int array[], int size); 
void bubblesort(int array[], int size);
int findinteger(int array[], int size, int search);

int main(){
	int array1[COUNT] = {5, 9, 3, 1, 7, 2, 8, 0, 4, 6};
    int array2[COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array3[COUNT]; 
    int i;
	
	print(array1, COUNT);
	print(array2, COUNT);
	
	printf("The sum of array1 is %d\n", sum(array1, COUNT));
	printf("The sum of array2 is %d\n", sum(array2, COUNT));
	
    compare(array1,  array2, COUNT);
	printf("Result is %d\n", testsorted(array1, COUNT));
	bubblesort(array1, COUNT);
	print(array1, COUNT);
	
	int search;
	printf("\n Enter a number: ");
	scanf("%d", &search);
	printf("It is in index %d\n", findinteger(array1, COUNT, search));
}
	
//print each array element
void print(int array[], int size){
	int i;
	for(i=0;i<size;i++){
		printf("%d ",array[i]);
	}
    printf(" \n");
}

//print the sum
int sum(int array[], int size){
	int i;
	int sum = 0;
	for(i=0;i<size;i++)
		sum += array[i];
	return sum;
}

//compare if two arrays have same elements
void compare(int array1[], int array2[], int size){
	int i;
	for(i=0;i<size;i++){
		if(array1[i] == array2[i])
		printf("They have same element.");
	 	break;
   	}
  	printf("They don't have same element.");
	printf(" \n");
}

//test if sorted
int testsorted(int array[], int size){
int ts =1; 
int i;
   for(i=0;i<size;i++){
   	if(array[i]<array[i+1]){
		ts+=1;
   	}
   }
	if(ts==size)
		return 1;
    else 
    	return 0;
}

//switch from small to large
void bubblesort(int array[], int size){
	int i, j, temp;
	for(i=0;i<size-1;i++) {
		for(j=size-1; j>=i; j--){
			if (array[j-1] > array[j]){
				temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}
}
//find integer
int findinteger(int array[], int size, int search){
	int begin = 0; 
	int end = size - 1;
	int mid;
    while(begin <= end){
		mid = (end + begin)/2;
		if(search > array[mid])
			begin = (mid + 1);
		else if(search == array[mid])
			return mid;
		else 
			end = (mid - 1);
	}
	return - 1;
}