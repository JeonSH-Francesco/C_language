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
snprintf는 C 또는 C++ 프로그래밍 언어에서 문자열을 형식화하여 지정된 버퍼에 저장하는 함수입니다. snprintf 함수는 "safe"나 "secure"한 형식화 함수로,
버퍼 오버플로우(버퍼의 크기를 초과하여 데이터를 쓰는 오류)를 방지하기 위해 사용됩니다.

snprintf 함수의 기본 구문은 다음과 같습니다:

int snprintf(char *str, size_t size, const char *format, ...);
여기서 각 매개변수의 역할은 다음과 같습니다.

str: 형식화된 문자열을 저장할 버퍼의 포인터입니다.
size: 버퍼의 크기를 나타내는 정수입니다. 이를 통해 str 버퍼에 저장되는 문자열의 길이를 제한할 수 있습니다.
format: 형식 지정자를 포함하는 문자열로, 출력 문자열의 형식을 지정하는 데 사용됩니다.
...: 형식 지정자로 지정된 데이터를 제공하는 추가 매개변수입니다.
snprintf 함수는 format 문자열을 기반으로 형식화된 문자열을 생성하고, 
이를 str 버퍼에 저장합니다. 그러나 size 매개변수를 통해 버퍼의 크기를 제한하므로 버퍼 오버플로우를 방지할 수 있습니다. 
만약 형식화된 문자열의 길이가 size보다 크다면 문자열은 size-1 문자로 잘립니다. 따라서 버퍼의 끝에는 널 종료 문자('\0')가 추가됩니다.

snprintf 함수는 형식 지정자를 사용하여 정수, 부동 소수점, 문자열 등 다양한 데이터 유형을 문자열로 변환할 수 있습니다. 이 함수는 문자열 생성 및 형식화 작업을 효과적으로 수행하면서도 버퍼 오버플로우로부터 보호해주는 중요한 문자열 처리 도구 중 하나입니다.


*/
