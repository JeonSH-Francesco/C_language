#include <stdio.h>

int main(){

char c1='A';
char* cp=NULL;
char** cpp= NULL;

cp=&c1;
cpp=&cp;

printf("c1: %c\t cp address: %x\t cpp address: %x\n",c1,cp,cpp);
printf("c1 address : %x\t cp address: %x\t cpp address:%x\n",&c1, &cp, &cpp);
printf("c1 value : %c\t c1 value *cp:%c\t c1 value **cpp : %c\t \n",c1,*cp, **cpp);

return 0;
}
