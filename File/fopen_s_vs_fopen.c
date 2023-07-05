#include <stdio.h>

int main() {
	char str[] = "Hello KISIA";

	FILE* fp=NULL;
	/*정수형 반환 0 또는 0이 아닌 값(파일을 제대로 읽어 오지 못함)*/

	if (fopen_s(&fp, "file.txt", "w") != NULL) {
		printf("File open error!");
		return 1;
	}

	fprintf(fp, "%s", str);

	fclose(fp);

	return 0;

}
/*
#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>

int main() {
	char str[] = "Hello KISIA";

	FILE* fp;
	fp = fopen("file.txt", "w");

	if (fp == NULL) {
		printf("File open error!");
		return -1;
	}

	fprintf(fp, "%s", str);

	fclose(fp);

	return 0;

}
*/
