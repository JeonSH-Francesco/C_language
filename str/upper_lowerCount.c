#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

int main() {
	FILE* fp;
	char c;

	fp = fopen("file.txt", "r");
	if (fp == NULL) {
		printf("File open error!");
		return 1;
	}

	while ((c = fgetc(fp)) != EOF) {
		if (isupper(c)) {
			c = tolower(c);
		}
		else if (islower(c)) {
			c = toupper(c);
		}
		putchar(c);
	}

	fclose(fp);

	return 0;
}
