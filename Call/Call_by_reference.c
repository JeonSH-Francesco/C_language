#include <stdio.h>

int func(int *i);

void main(){
    int a=10;
    int result = 0;

    result=func(&a);
    printf("%d\n",result);
    printf("%d\n",a);
}
/*
배열이나 구조체와 같은 데이터를 함수에 전달할 때는
주소에 의한 호출이 실행 시간과 메모리 공간 측면에서 좋은 성능을 제공합니다.
*/
int func(int *i){
    *i=*i+1;
    return *i;
}
