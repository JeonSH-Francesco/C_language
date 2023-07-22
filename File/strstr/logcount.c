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
	//while(!feof(fp))구문을 사용하면 파일의 끝에 도달하기 전 까지는 
	//0이 아닌 값을 반환 하므로,
	//파일의 끝에 도달한 이후에도 한 번 더 루프를 실행하게 됩니다.
	//이로 인해 cnt 변수가 예상보다 큰 값을 출력합니다.
	//따라서 이를 해결하기 위해 fgets 함수를 이용하여 
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		if (strstr(buf, ans) != NULL) {
			cnt++;
		}
	}

	printf("%d", cnt);

	fclose(fp);

	return 0;
}

//->출력결과 : 78

/*
fopen_s 버전
#include <stdio.h>
#include <string.h>

int main() {
	char buf[100];
	char ans[] = "ERROR";

	int cnt = 0;
	FILE* fp = fopen_s(&fp,"log.txt", "r");

	if (fopen_s(&fp, "log.txt", "r") != NULL) {
		printf("File open error!");
		return 1;
	}
	//while(!feof(fp))구문을 사용하면 파일의 끝에 도달하기 전 까지는 
	//0이 아닌 값을 반환 하므로,
	//파일의 끝에 도달한 이후에도 한 번 더 루프를 실행하게 됩니다.
	//이로 인해 cnt 변수가 예상보다 큰 값을 출력합니다.
	//따라서 이를 해결하기 위해 fgets 함수를 이용하여 
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		if (strstr(buf, ans) != NULL) {
			cnt++;
		}
	}

	printf("%d", cnt);

	fclose(fp);

	return 0;
}
*/


//->아래 출력 결과 : 79
/*
잘못된 C 코드
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
		//printf("%s", buf);
		
		if (strstr(buf, ans) != NULL) {
			//printf("%s", buf);
			cnt++;
		}
	}
	printf("%d", cnt);

	fclose(fp);

	return 0;
}
*/
