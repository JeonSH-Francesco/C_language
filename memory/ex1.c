#include <stdio.h>


/*
코드 영역 : 프로그램 실행 코드, 함수들이 저장되는 영역
스택 영역 : 함수 호출에 의한 매개변수와 지역변수 함수, 반복문, 조건문의 중괄호 내부에 정의된 변수들이 저장되는 영역
->잠깐 사용되고 메모리에서 소멸시킬 데이터가 저장되는 영역
데이터 영역 : 전역 변수와 정적 변수들이 저장되는 영역으로 프로그램이 종료 될 때까지 유지되어야 하는 데이터가 저장되는 영역
힙 영역 : 프로그램이 실행 되는 동안에 프로그래머가 동적으로 메모리를 할당할 수 있는 영역
->즉, 프로그래머가 마음대로 사용할 수 있는 영역

*/


int a=10;

int main(void){

    int num1=10, num2=20;
    static int s=30;

    printf("Data : %d %d %d %d\n",a,num1,num2,s);
    printf("Code area : %x %x\n",main, printf);
    printf("Stack area : %x %x\n",&num1, &num2);
    printf("Data area : %x %x\n", &a, &s);

    return 0;
}
