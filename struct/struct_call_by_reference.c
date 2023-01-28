#include <stdio.h>
/*
구조체와 함수
1. 구조체를 함수의 인자로 전달하기(값에 의한 호출과 주소에 의한 호출)
2. 구조체를 함수의 반환형으로 전달하기(값 반환과 주소 반환)

2의 경우 p의 주소가 구조체 포인터 변수 call에 저장
*/
struct point
{   int x;
    int y;
};

void function(struct point *call);

int main(){
    struct point p={10,20};
    function(&p);

    return 0;
};

void function(struct point *call){
  printf("%d %d\n",call->x,call->y);
  printf("%d %d\n",(*call).x,(*call).y);
}
