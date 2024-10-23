#include <stdio.h>

int main() {
	int array1[2][4] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int array2[4][2] = { 0 };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			array2[j][1 - i] = array1[i][j];
			printf("array1[%d][%d]=%d\t", i, j, array1[i][j]);
			printf("array2[%d][%d]=%d\n",j,1-i, array2[j][1- i]);
		}
	}

	return 0;
}



/*90도 회전하는 결과가 되도록 출력하기
단, 출력은 오름차순 순으로
array1[0][0]=1  array2[0][0]=5
array1[0][1]=2  array2[1][0]=6
array1[0][2]=3  array2[2][0]=7
array1[0][3]=4  array2[3][0]=8
array1[1][0]=5  array2[0][1]=1
array1[1][1]=6  array2[1][1]=2
array1[1][2]=7  array2[2][1]=3
array1[1][3]=8  array2[3][1]=4

result : 
array1[0][0]=1  array2[0][1]=1
array1[0][1]=2  array2[1][1]=2
array1[0][2]=3  array2[2][1]=3
array1[0][3]=4  array2[3][1]=4
array1[1][0]=5  array2[0][0]=5
array1[1][1]=6  array2[1][0]=6
array1[1][2]=7  array2[2][0]=7
array1[1][3]=8  array2[3][0]=8
*/
