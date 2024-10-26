#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	char input[] = "name=JohnDoe&age=30&city=NewYork";  // 입력 문자열
	char* token = strtok(input, "&");  // 첫 번째 토큰을 가져옵니다.
	int i = 0;

	char temp[3][50]; // 각 토큰을 저장할 배열 (최대 3개 토큰, 각 최대 길이 50)

	while (token != NULL) {
		// 현재 토큰 출력
		printf("token : %s\n", token);  // 현재 토큰 출력
		strcpy(temp[i], token); // 토큰을 temp 배열에 저장
		printf("Stored temp[%d]: %s\n", i, temp[i]); // 저장된 토큰의 인덱스 출력
		i++;
		token = strtok(NULL, "&"); // 다음 토큰으로 이동
	}

	// Final stored tokens을 기준으로 '='을 기준으로 분리하여 출력
	printf("\nFinal output:\n");
	for (int j = 0; j < i; j++) {
		char* key = strtok(temp[j], "="); // '='을 기준으로 키를 분리
		char* value = strtok(NULL, "=");   // '=' 이후의 값을 분리
		if (value != NULL) { // 값이 존재하는 경우 출력
			printf("%s : %s\n", key, value);
		}
	}

	return 0;
}
