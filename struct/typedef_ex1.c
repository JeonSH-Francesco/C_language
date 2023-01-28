#include <stdio.h>

typedef struct score{
    int math;
    int english;
    int average;

}SCORE; //typedef를 사용하는 방법 1 -> 구조체 정의와 typedef 선언

struct student{
    int no;
    SCORE s;
};

typedef struct student Student; //typedef를 사용하는 방법 2->구조체 정의와 개별적으로 선언

int main(void){
    Student stu={201921270,100,100,0};
    stu.s.average=(stu.s.math+stu.s.english)/2;
    printf("학번 : %d\n",stu.no);
    printf("평균 : %d\n",stu.s.average);
}
