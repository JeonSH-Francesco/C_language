#include <stdio.h>
/*
구조체에서 포인터를 사용하는 경우는
1. 멤버 변수로 포인터 사용하기
2. 구조체 변수로 포인터 사용하기
3. 자기 참조 구조체와 외부 참조 구조체

3번의 경우
*/
struct student{
    char name[20];
    int money;
    struct student* left_link;
    struct student* right_link;
};

int main(void){
    struct student stu1={"Jeon",90,NULL,NULL};
    struct student stu2={"Lee",80,NULL,NULL};
    struct student stu3={"Goo",100,NULL,NULL};

    stu1.left_link=&stu2;
    stu1.right_link=&stu3;

    printf("%s %d\n",stu1.name,stu1.money);
    printf("%s %d\n",stu1.left_link->name,stu1.left_link->money);
    printf("%s %d\n",stu1.right_link->name,stu1.right_link->money);

    return 0;
}
