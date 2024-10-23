#include <stdio.h>

// 피보나치 재귀 함수
int fibonacci(int n) {
	if (n == 0) {
		return 0; // 0번째 피보나치 수
	}
	else if (n == 1) {
		return 1; // 1번째 피보나치 수
	}
	return fibonacci(n - 1) + fibonacci(n - 2); // 재귀 호출
}

int main() {
	int num = 0;
	printf("Input number : ");
	scanf_s("%d", &num);

	for (int i = 0; i <num; i++) {
		printf("%d ", fibonacci(i));
	}
	return 0;
}
