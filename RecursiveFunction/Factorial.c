#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int main() {
    int num;
    printf("정수를 입력하세요: ");
    scanf("%d", &num);

    unsigned long long fact = factorial(num);

    printf("%d! = %llu\n", num, fact);

    return 0;
}
