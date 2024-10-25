#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 80

int main() {
    char* src = "abcdefg1234567";
    char* dest=(char*)malloc(sizeof(char)*MAX_STR_LEN);
    char* key = "123";
    char* pos;
    
    pos=strstr(src, key);

    printf("src: %s, index : %d\n",src,pos-src);

    strncpy(dest, src, pos - src);
    dest[pos - src] = '\0';
    strncat(dest, pos + strlen(key), strlen(pos + strlen(key)));
    printf("pos+strlen(key): %s\n", pos + strlen(key));
    printf("dest : %s\n",dest);


    free(dest);

    return 0;
}

