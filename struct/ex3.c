#include <stdio.h>
#include <string.h>

struct student{
    char no[10];
    char name[20];
};

int main(void){
    int i=0;
    struct student stu;

    /*
    구조체에 멤버 변수를 배열로 사용했을 때
    배열의 이름은 시작 주소이기 때문에 문자열을 저장하고 있으므로 당연히
    stu.no="2019";
    stu.name="AAA";
    ->에러 발생한다.
    따라서 strcpy, strncpy를 이용하여 저장한다.
    */
    strcpy(stu.no,"2019");
    strcpy(stu.name,"AAA");

    printf("학번 :%s 이름 : %s\n",stu.no, stu.name);
    return 0;

}
