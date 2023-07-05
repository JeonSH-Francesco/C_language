#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	unsigned char buf[11];
	FILE* fp = fopen("example.bin", "rb");

	if (fp == NULL) {
		printf("Error : File open failed");
		return -1;
	}
	fread(buf, sizeof(unsigned char), 10, fp);

	for (int i = 0; i < 10; i++) {
		//printf("[%d] : %02x", i, buf[i]);
		printf("%02x ",buf[i]);
	}
	printf("\n");

	fclose(fp);

	return 0;
}
------
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	unsigned char buf[10]; // 버퍼를 unsigned char 배열로 선언하여 16진수로 출력합니다.
	FILE* fp = fopen("example.bin", "rb");

	if (fp == NULL) {
		printf("Error: File open failed");
		return -1;
	}

	while (fread(buf, sizeof(unsigned char), 10, fp) > 0) {
		for (int i = 0; i < 10; i++) {
			printf("%02X ", buf[i]); // 16진수로 출력하기 위해 %02X를 사용합니다.
		}
		putchar('\n');
	}

	fclose(fp);

	return 0;
}
*/
