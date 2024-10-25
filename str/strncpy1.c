#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 80

int main() {
    char* src = "abcdefg1234567";
    char* dest = (char*)malloc(sizeof(char) * MAX_STR_LEN);

    strncpy(dest, src, 7);
    dest[7] = '\0';

    printf("src: %s\n", src);
    printf("dest: %s\n", dest);

    free(dest);
    return 0;
}
