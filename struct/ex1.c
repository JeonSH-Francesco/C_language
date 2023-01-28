#include <stdio.h>

struct student{
    char no[10];
    char name[20];
    int math;
    int english;
    int total;
};

int main(void){

    struct student stu1={"2019","JSH",100,100,0};


    stu1.total=stu1.english+stu1.math;
    printf("%s %s",stu1.no,stu1.name);
    printf("\n");

    printf("총점 : %d",stu1.total);


}
