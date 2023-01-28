#include <stdio.h>
/*
구조체에서 포인터를 사용하는 경우는
1. 멤버 변수로 포인터 사용하기
2. 구조체 변수로 포인터 사용하기
3. 자기 참조 구조체와 외부 참조 구조체

2번의 경우
*/
struct student{
    char no[10];
    char name[20];
    double total;
};

int main(void){
    struct student stu={"201921270","Jeon",180};
    struct student *p = NULL;   //구조체 변수 1차원 포인터 선언
    struct student **pp= NULL;


    p=&stu;
    pp=&p;


    printf("%s %s %lf\n",stu.no,stu.name,stu.total);

    printf("%s %s %lf\n",(*p).no,(*p).name,(*p).total); //1차원 포인터를 이용한 접근
    printf("%s %s %lf\n",p->no, p->name, p->total);

    printf("%s %s %lf\n",(**pp).no,(**pp).name,(**pp).total);
    printf("%s %s %lf\n",(*pp)->no,(*pp)->name,(*pp)->total);

    return 0;
}
