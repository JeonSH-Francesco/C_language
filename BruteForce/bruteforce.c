#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_password_length 99

int main() {
    char *key = (char*)malloc((max_password_length + 1) * sizeof(char)); // 동적 할당으로 메모리를 할당합니다.
    if (key == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    size_t i = 0; // size_t로 변경
    unsigned char j = 0; // unsigned char로 변경

    printf("Input your password : ");
    scanf("%99s", key); // 최대 길이를 99로 제한하여 오버플로우를 방지합니다.

	//printf("size : %d\n",strlen(key));
    for (i = 0; i < strlen(key); i++) { // i를 size_t와 비교
        for (j = 0; j <= 127; j++) {
            if ((unsigned char)j == key[i]) { // j를 unsigned char로 변경
                key[i] = (unsigned char)j;
            }
        }
    }

    printf("Brute force success! Password found: %s\n", key);

    free(key); // 동적으로 할당한 메모리를 해제합니다.

    return 0;
}
/*#include <stdio.h>
char pw[5] = "Sdev";

int main() {
	
	char key[5]="aaaa";
	int i = 0;
	int j = 0;

	for (i = 0; i <4; i++) {
		for (j = 'A'; j <='z'; j++) {
			if ((char)j == pw[i]) {
				key[i] = (char)j;
			}
		}
	}
	printf("Brute force success! Password found: %s\n", key);

	return 0;
	
}
*/
