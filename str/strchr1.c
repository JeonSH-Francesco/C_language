#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 80

int main(){
    char *src= "abcdefg1234567";
    char *pos;

    pos=strchr(src,'f');
    printf("src : %s, pos : %p, *pos :%c\n",src,pos,*pos);

    return 0;
}
