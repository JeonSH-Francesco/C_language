// ‘^(?=.[A-Z]).+$’를 해석하고, 직접 구현하여 테스트하시오.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 대문자로 시작하는 부분을 검색하는 함수
const char* find_upper_start(const char* string) {
	while (*string && !(*string >= 'A' && *string <= 'Z'))
		string++;
	return string;
}

int main()
{
	const char* string1 = "!Abc123#";
	const char* string2 = "!bbc123#";
	char dest[100] = { 0, };

	const char* ptr1 = find_upper_start(string1);
	const char* ptr2 = find_upper_start(string2);

	if (*ptr1) {
		// 대문자로 시작하는 부분을 dest에 복사
		strcpy(dest, ptr1);
		printf("%s\n", dest);
	}
	else {
		printf("No match found in string1.\n");
	}

	if (*ptr2) {
		// 대문자로 시작하는 부분을 dest에 복사
		strcpy(dest, ptr2);
		printf("%s\n", dest);
	}
	else {
		printf("No match found in string2.\n");
	}

	return 0;
}
