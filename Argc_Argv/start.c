
#include <stdio.h>

//int argc = main() 함수에 전달되는 데이터의 갯수를 뜻한다.
//char *argv[] = main() 함수에 전달되는 실제적인 데이터로 char형 포인터 배열로 구성되어 있다.
//첫 번째 문자열은 프로그램의 실행 경로이다.

int main(int argc,char* argv[]){
    int i=0;
    printf("문자열 수 : %d\n",argc);

    for(i=0;i<argc;i++){
        printf("argv[%d] : %s\n",i,argv[i]);
    }

    return 0;
}
