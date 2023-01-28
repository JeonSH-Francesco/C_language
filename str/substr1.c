#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 80

int main(){
    char *src= "abcdefg1234567abcdefghi";
    char *pos;
    char *substr=(char*)malloc(sizeof(char)*MAX_STR_LEN);


    pos=strchr(src,'f');
    printf("src : %s, pos : %p, *pos :%c\n",src,pos,*pos);
    printf("src: %p, pos: %p, *pos: %c\n", src, pos, *pos);
    printf("%s\n",pos+1);

    strncpy(substr,src,pos-src);
    printf("%s\n",substr);

    free(substr);

    return 0;
}
