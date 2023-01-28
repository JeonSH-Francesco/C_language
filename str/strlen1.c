#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 80

int main(){
    char *src= "abcdefg1234567";
    char *dest=(char*)malloc(sizeof(char)*MAX_STR_LEN);
    char *key="123";
    char *pos;

    pos=strstr(src,key);
    printf("src: %s, index : %ld\n",src,pos-src);

    strncpy(dest,src,pos-src);

    strncat(dest, pos+strlen(key), strlen(pos-strlen(key)));

    printf("pos+strlen(key): %s\n",pos+strlen(key));
    printf("strlen(pos-strlen(key)): %d\n",strlen(pos-strlen(key)));
    printf("dest: %s",dest);

    free(dest);

    return 0;
}
