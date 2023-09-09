#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int user_input = 1234555555555555555;
    char buffer[10];

    // 보안에 취약한 sprintf 사용
    sprintf(buffer, "%d", user_input);

    printf("문자열: %s\n", buffer);

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>

int main() {
    int user_input = 12345;
    char buffer[10];

    // snprintf를 사용하여 버퍼 오버플로우 방지
    int result = snprintf(buffer, sizeof(buffer), "%d", user_input);

    if (result >= 0 && result < sizeof(buffer)) {
        printf("문자열: %s\n", buffer);
    }
    else {
        printf("버퍼 크기 초과!\n");
    }

    return 0;
}
*/
