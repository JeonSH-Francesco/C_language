#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 80

int main(){
    char *src= "abcdefg1234567abcdefghi";
    char *pos, *pos1;

    pos = strchr(src,'f');

    printf("src : %s, pos : %p, *pos: %c\n",src,pos,*pos);
    printf("src: %p, pos: %p, *pos: %c idx=%ld\n",src,pos,*pos,pos-src);


    pos1=strchr(pos+1,'f');

    printf("pos+1 : %s, pos1 : %p, *pos1 : %c\n",pos+1,pos1,*pos1);
    printf("pos+1 : %p, pos1 : %p, *pos1 :%c idx=%ld\n",pos+1,pos1,*pos1,pos1-src);


    return 0;
}
