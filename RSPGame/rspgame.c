#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int com, user;
	srand((unsigned)time(NULL)); // rand 값 매번 결과가 다르게 시드 값 설정

	printf("가위 바위 보 게임을 시작합니다.");
  //횟수, 결과 루틴 추가해도 됨. 일단은 생략함.
	while (1) {
		com = rand() % 3 + 1; //1~3 값 중 하나 랜덤하게 발생

		printf("(1 :가위, 2 :바위, 3 :보 / 0 :종료)\n\n");
		printf("Input Number :");
		scanf_s("%d", &user);
		if (user > 0 && user < 4) {
			printf("Com : %d, User : %d\n", com, user);

			if (com == user) {
				printf("비겼습니다.\n");
			}
			else if ((com == 1) && (user == 3) || (com == 2) && (user == 1) || (com == 3) && (user == 2)) {
				printf("졌습니다.\n");
			}
			else {
				printf("이겼습니다.");
			}

		}
		else {
			if (user == 0) {
				printf("게임을 종료합니다.");
				break;
			}
			printf("숫자를 제대로 입력해주세요\n\n");
		}
		

	}

	return 0;


}
