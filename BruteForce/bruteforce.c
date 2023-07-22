#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_password_length 99

int main() {
    char* key = (char*)malloc((max_password_length + 1) * sizeof(char));
    char* mitmkey = (char*)malloc((max_password_length + 1) * sizeof(char));

    if (key == NULL || mitmkey == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    size_t i = 0;
    unsigned char j = 0;

    printf("Input your password :");
    scanf("%99s", key);

    memset(mitmkey, 0, (max_password_length + 1) * sizeof(char)); // mitmkey 배열을 0으로 초기화

    for (i = 0; i < strlen(key); i++) {
        for (j = 0; j < 127; j++) {
            if ((unsigned char)j == key[i]) {
                mitmkey[i] = (unsigned char)j;
            }
        }
    }

    printf("Brute force success! Password found: %s\n", mitmkey);

    free(key); // 동적으로 할당한 메모리를 해제합니다.
    free(mitmkey);
    return 0;
}
/*
#include <stdio.h>
char pw[5] = "sdev";

int main() {
	
	char key[5]="aaaa";#include <stdio.h>

int main() {
    char* key; // Declare key as a pointer

    printf("Input your password: ");
    scanf("%s", &key); 
    
    size_t i = 0;
    unsigned char j = 0;
    
    for (i = 0; i<strlen(key); i++) {
        for (j = 'A'; j <= 'z'; j++) {
            if ((unsigned char)j == key[i]) {
                key[i] = (char)j;
            }
        }
    }  

    printf("Brute force success! Password found: %s\n", key);

    return 0;
}

*/
