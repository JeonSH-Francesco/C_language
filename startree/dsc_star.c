#include <stdio.h>

int main() {
	int i = 0;
	int j = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i <= j) {
				printf("*");
			}
		}
		printf("\n");
	}

	return 0;

}

/*
result :
*****
****
***
**
*

*/
