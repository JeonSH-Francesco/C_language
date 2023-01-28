#include <stdio.h>

char str1[] = "1234567890";
char str2[] = "abcdefghijklmnopqrstuvwxyz";

int get_length(char *str);


int main() {
    int i=0;
    printf("str1: %s, len: %d\n", str1, get_length(str1));
    printf("\n");
    printf("str2: %s, len: %d\n", str2, get_length(str2));

    printf("\nreverse : ");
    for(i=strlen(str1)-1;i>=0;i--){
    printf("%c ",str1[i]);
    }
    printf("\n");
    printf("reverse : ");
    for(i=strlen(str2)-1;i>=0;i--){
    printf("%c ",str2[i]);
    }
    printf("\n");
return 0;
}

int get_length(char *str) {
    char *ch =str;
    int len=0;

    while(*ch!='\0'){
        printf("%c",*ch);
        ch++; len++;
    }
    printf("\n");

    return len;
}
