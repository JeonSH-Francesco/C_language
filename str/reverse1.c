#include <stdio.h>           // printf 함수, scanf_s 함수를 사용하기 위해!
#define MAX_LENGTH     64    // 최대 64자까지만 입력 받는다.

int main()
{
    int i, len = 0;
    char str[MAX_LENGTH];

    printf("Input String : ");
    // scanf 함수를 사용하려면 scanf("%[^\n]s", str); 라고 적으면 됩니다.
    // %s라고만 적으면 공백을 구분자로 봐서 입력을 공백까지만 받기 때문에
    // 아래와 같이 '형식 지정자'를 사용해야지 공백도 포함해서 입력 받습니다.
    scanf_s("%[^\n]s", str, MAX_LENGTH - 1);

    // 사용자가 입력한 str 배열에 입력된 문자열의 길이를 구한다.
    while (str[len] != 0) len++;

    printf("-> ");
    for (i = len -1 ; i >= 0; i--) {
        printf("%c", str[i]);   // 문자 단위로 출력
    }
    // 줄바꿈을 한다.
    printf("\n");
    return 0;
}
