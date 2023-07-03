#include <stdio.h>

int main() {

	for (int i = 0; i < 3; i++) {//라인 핸들링
		for (int j = 0; j <=i; j++) { //i개 만큼의 별을 찍는 과정
			printf("*");
		}
		printf("\n");
	}

	printf("\n");

	int k=0;
	int l = 0;

	while (k< 3) { //라인 핸들링
		k++;
		l = 0; //초기화 과정 필요->그래야 l만큼의 별을 찍을 수 있다.

		while (l < k) {
			l++;
			printf("*");
			
		}
		printf("\n");
	}

}
