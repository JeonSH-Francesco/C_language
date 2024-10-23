#include <stdio.h>

int increase() {
	static int x = 0; // 정적 변수 x는 한 번만 초기화되고 유지됩니다.
	x += 2;          // x의 값이 2씩 증가합니다.
	return x;       // 증가한 x의 값을 반환합니다.
}

int main() {
	int x = 0;      // 지역 변수 x
	int sum = 0;    // 합계를 저장할 변수
	printf("i\t sum\t x\n"); // 헤더 출력
	printf("------------------------\n");
	for (int i = 0; i < 4; i++) {
		x++;          // 지역 변수 x를 증가
		sum += increase(); // increase() 함수 호출 후 반환값을 sum에 더함
		printf("%d\t %d\t %d\n", i, sum, x); // i, sum, x의 값을 출력
	}
	printf("정적 변수 static 변수는 중괄호 내에서 초기화 될때 메모리 생성이 되고, 한 번만 수행된다!\n");
	printf("처음에 초기화된 값이 이후에 함수가 호출될 때마다 업데이트 된다!\n");
	return 0;
}

/*
i        sum     x
------------------------
0        2       1
1        6       2
2        12      3
3        20      4

*/
