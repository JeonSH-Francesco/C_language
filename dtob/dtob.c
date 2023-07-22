#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int x;
	printf("Enter Number(Decimal) : ");
	scanf("%d", &x);

	printf("To Binary : ");

	for (int i = 7; i >= 0; i--) {
		int tmp = (x >> i) & 1;
		printf("%d", tmp);
	}
	return 0;
}
//비트 연산 하는 방법

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int i=0;
	int decimal = 0;
	int binary[8]={};

	printf("Enter Number (Decimal): ");
	scanf("%d", &decimal);

	if (decimal == 0) {
		printf("Binary: 0\n");
		return 0;
	}

	printf("Binary: ");
	while (decimal > 0) {
		binary[i] = decimal % 2;
		decimal = decimal / 2;
        	i++;
	}
    for(int j=i-1;j>=0;j--){
        printf("%d",binary[j]);
    }
	printf("\n");

	return 0;
}
//단순 계산 하는 방법
*/
