#include <stdio.h>

struct score
{
    int math;
    int english;
    int total;
};

struct student{
    int no;
    struct score s;

};

int main(){
    struct student stu={201921270,{90, 80,0}};

    stu.s.total=stu.s.math+stu.s.english;

    printf("학번 : %d\n",stu.no);
    printf("총합 : %d\n",stu.s.total);
