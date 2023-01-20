#include <stdio.h>


//포인터 변수의 크기는 4byte(x86) 8byte(x64)
//함수 포인터도 포인터 변수이기 때문에 4byte 크기의 메모리 공간을 갖는다.

void add(int num1, int num2);
void subtract(int num1, int num2);

int main(){
    int x,y;
    char c;

    void(*pointer)(int,int);


    printf("add 함수의 주소 : %x\n",add);
    printf("subtract 함수의 주소 : %x\n",subtract);


    printf("Input : ");
    scanf("%d %c %d",&x,&c,&y);

    if(c=='+'){
        pointer = add;
    }
    else if(c=='-'){
        pointer = subtract;
    }
    else{
        printf("두번째 연산자는 + 또는 -를 입력하세요.\n");

    }
    pointer(x,y);
    return 0;
}

void add(int num1,int num2){
int result;
result = num1+ num2;
printf("%d + %d = %d입니다.\n",num1,num2,result);
}


void subtract(int num1,int num2){

int result;
result = num1- num2;
printf("%d - %d = %d입니다.\n",num1,num2,result);
}
