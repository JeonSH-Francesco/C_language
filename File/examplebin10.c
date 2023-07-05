#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	unsigned char buf[11]; // 버퍼를 unsigned char 배열로 선언하여 16진수로 출력합니다.
	FILE* fp = fopen("example.bin", "rb");

	if (fp == NULL) {
		printf("Error: File open failed");
		return -1;
	}

	fread(buf, sizeof(unsigned char), 10, fp);

	for (int i = 0; i < 10; i++) {
		printf("[%d] %02x ", i, buf[i]); // 16진수로 출력하기 위해 %0x %02x가 있는데 두 자리로 출력하기 위해 %02x로 함.
	}

	fclose(fp);

	return 0;
}
