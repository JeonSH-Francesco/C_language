#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void det(int num) {
	int i = 0;
	int cnt = 0;

	for (i = 2; i < num; i++) {
		if (num % i == 0) {
			cnt = 1;
			break;
		}
	}

	if (cnt == 0 && num > 1) {
		printf("%d is a prime number.\n", num);
	}
	else {
		printf("%d is not a prime number.\n", num);
	}
}

int main() {
	int num = 0;
	printf("Input number: ");
	scanf("%d", &num);

	det(num);

	return 0;
}
