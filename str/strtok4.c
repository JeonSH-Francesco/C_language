#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char input[] = "name=JohnDoe&age=30&city=NewYork";  // 입력 문자열
	char* token = strtok(input, "&");  // 첫 번째 토큰을 가져옵니다.
	char** temp = malloc(3 * sizeof(char*)); // 동적 할당된 포인터 배열 (최대 3개 토큰)

	for (int i = 0; i < 3; i++) {
		temp[i] = malloc(50 * sizeof(char));
	}
	int i = 0;

	// 각 토큰을 처리
	while (token != NULL) {
		//현재 토큰 출력
		printf("token: %s\n",token);
		strcpy(temp[i],token);
		printf("Stored temp[%d]:%s\n",i,temp[i]);//저장된 토큰의 인덱스 출력
		i++;
		token = strtok(NULL, "&");
	}

	//Final stored tokens을 기준으로 '='을 기준으로 분리하여 출력
	printf("\nFinal output:\n");
	for (int j = 0; j < i; j++) {
		char* key = strtok(temp[j], "="); //"="을 기준으로 키를 분리
		char* value = strtok(NULL, "="); //"=" 이후의 값을 분리
	
		if (value != NULL) {
			printf("%s: %s\n",key, value);
		}
	}
	//동적으로 할당한 메모리 해제
	for (int k = 0; k < 3; k++) {
		free(temp[k]); // 각 문자열에 대한 메모리 해제
	}
	free(temp); //포인터 배열에 대한 메모리 해제

	return 0;
}




/*token: name=JohnDoe
Stored temp[0]:name=JohnDoe
token: age=30
Stored temp[1]:age=30
token: city=NewYork
Stored temp[2]:city=NewYork

Final output:
name: JohnDoe
age: 30
city: NewYork
*/
