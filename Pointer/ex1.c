#include <stdio.h>
//함수의 선언부
void func(char a,char *b,int c, double d);

int main(void){

    char c='A';
    char *str="ABCD";//char 형 포인터 변수 선언
    int num1=10;
    double num2=3.14;
    //함수의 호출
    func(c,str,num1,num2);
    return 0;

}
//함수의 정의부
void func(char a,char *b, int c, double d)
{printf("%c %s %d %.2lf\n",a,b,c,d);}
