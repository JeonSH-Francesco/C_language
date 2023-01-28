#include <stdio.h>

char *string1(char *s);

int main(void){
    char *p1=NULL;
    static char str[]="Good";
    p1=string1(str);

    printf("%s\n",p1);
}

char *string1(char *s){
    return s;
}
