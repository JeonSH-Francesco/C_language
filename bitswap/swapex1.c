#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>


int main() {
	int num1 = 10;
	int num2 = 20;

	int* ptr1 = &num1;
	int* ptr2 = &num2;


	printf("Before swap:\n");
	printf("num1: %d\n", num1);
	printf("num2: %d\n", num2);

	*ptr1 ^= *ptr2;
	*ptr2 ^= *ptr1;
	*ptr1 ^= *ptr2;

	printf("\nAfter swap:\n");
	printf("num1: %d\n", num1);
	printf("num2: %d\n", num2);

	return 0;
}
