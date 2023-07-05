#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	char buf[100];
	char ans[10] = "ERROR";

	int cnt = 0;
	FILE* fp = fopen("log.txt", "r");

	if (fp == NULL) {
		printf("File open error!");
		return -1;
	}

	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
		
		if (strstr(buf, ans) != NULL) {
			printf("%s", buf);
			cnt++;
		}
	}
	printf("%d", cnt);

	fclose(fp);

	return 0;
}
