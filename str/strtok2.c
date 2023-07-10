#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "Hello, world! How are you?";
	char* token;

	token = strtok(str, " ");

	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	return 0;
}
