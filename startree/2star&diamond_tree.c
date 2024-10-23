#include <stdio.h>

int main() {

	int line, space, star;

	for (line = 1; line < 5; line++) {
		//공백 출력
		for (space = 1; space < 5 - line; space++) {
			printf(" ");
		}
		//별 출력
		for (star = 0; star < 2 * line - 1; star++) {
			printf("*");
		}

		printf("\n");
	}

	return 0;

}
/*
result:

   *
  ***
 *****
*******
*/

/*

-------------------
#include <stdio.h>

int main() {
	int line, space, star;

	for (line = 1; line < 5; line++) {
		for (space =1; space<line; space++) {
			printf(" ");
		}
		for (star = 0; star < 2 * (5-line)-1; star++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}



result:
*******
 *****
  ***
   *


-------------------
#include <stdio.h>

int main() {
	int line, space, star;

	//상단 피라미드 부분
	for (line = 0; line < 5; line++) {
		//공백 출력
		for (space = 0; space < 5 - line - 1; space++) {
			printf(" ");
		}
		//별 출력
		for (star = 0; star < 2 * line + 1; star++) {
			printf("*");
		}
		printf("\n");
	}

	//하단 피라미드 부분
	for (line = 3; line >= 0; line--) {
		//공백 출력
		for (space = 0; space < 5 - line - 1; space++) {
			printf(" ");
		}
		//별 출력
		for (star = 0; star < 2 * line + 1; star++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}

result:
	*
   ***
  *****
 *******
*********
 *******
  *****
   ***
	*
-------------------

*/
