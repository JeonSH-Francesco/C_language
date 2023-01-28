#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 80

int main(){
    char *src="abcdefg1234567";
    char *dest=(char*)malloc(sizeof(char)*MAX_STR_LEN);

    strcpy(dest,src);

    printf("src: %s\n",src);
    printf("dest: %s\n",dest);

    free(dest);
    return 0;
}
