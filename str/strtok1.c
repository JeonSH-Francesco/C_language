#include <stdio.h>
#include <string.h>

/*
char *str은 포인터라서 주소를 담고, 문자열의 값을 변경 불가
char str[]은 배열이라서 값을 담기 때문에 문자열 값 변경 가능
->배열 선언시 컴파일러가 알아서 배열 최대 개수를 할당함.

*/

int main(){
    char *str1="Hello C World";
    char str2[]="Hello C World";

    //char *ptr=strtok(str1," "); error 허용 X

    char *ptr=strtok(str2," ");
    while(ptr!=NULL){
        printf("%s\n",ptr);
        ptr=strtok(NULL, " ");
    }


}
