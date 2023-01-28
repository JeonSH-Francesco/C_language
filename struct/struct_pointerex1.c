#include <stdio.h>
/*
구조체에서 포인터를 사용하는 경우는
1. 멤버 변수로 포인터 사용하기
2. 구조체 변수로 포인터 사용하기
3. 자기 참조 구조체와 외부 참조 구조체

1번의 경우
*/
struct point {
    int *x;
    int *y;
};

int main(void){
    int num1=4;
    int num2=5;
    struct point p1;


    p1.x=&num1;
    p1.y=&num2;

    printf("%d %d\n",num1,num2);
    printf("%d %d\n",*p1.x,*p1.y);

}
