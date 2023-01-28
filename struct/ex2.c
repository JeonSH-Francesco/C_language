#include <stdio.h>

//구조체 변수로 배열 사용하기

struct student{
    char no[10];
    char name[20];
    double total;
};

int main(void){
    struct student stu[3];
    /*
    struct student stu[3]={
    {}
    {}
    {}
    };형식으로 해도 됨.
    */
    int i=0;

    for(i=0;i<3;i++){
        printf("학번 이름 총점 순으로 입력하세요 : ");
        scanf("%s %s %lf",stu[i].no, stu[i].name, &stu[i].total);
    }


    printf("3명의 학생 정보를 출력합니다. \n");
    for(i=0;i<3;i++){
        printf("%s %s %.2lf",stu[i].no, stu[i].name, stu[i].total);
        printf("\n");
    }
    return 0;

}
