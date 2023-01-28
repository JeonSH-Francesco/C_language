#include <stdio.h>


int func(int i);

void main(){
    int a=10;
    int result= 0;

    result = func(a); // call by value
    printf("%d\n",result);
    printf("%d",a);

}
/*
값에 의한 호출은 함수를 호출할 때 제약이 있습니다. 함수에 대량의 데이터를 전달해야 하는 경우,
함수의 매개변수(지역 변수)들이 늘어나서 이들이 하나씩 스택에 쌓이는데 많은 시간과 메모리 공간을 필요로 하기 때문에
주소에 의한 호출이 필요함.

*/

int func(int i){
    i=i+1;
    return i;
}
