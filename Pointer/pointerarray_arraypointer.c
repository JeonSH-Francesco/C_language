#include <stdio.h>
int main()
{
    int i, j;
 	 	
    /* 포인터 배열 -> 주소 값을 저장하는 배열*/
 	int a=1, b=2, c=3;
 	int *ptrArr[3]={&a,&b,&c};
 	
 	
 	for(i=0;i<3;i++)
		printf("%d ", *(ptrArr[i]));
 	
 	printf("\n");
 	printf("\n");
	 /* 배열 포인터 -> 배열의 시작 주소 값을 저장하는 포인터*/
 	int arr[2][3] ={1,2,3,4,5,6};
 	int(*arrPtr)[3]=arr;
 	
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			printf("%d ",arrPtr[i][j]);
		}
		printf("\n");
	}
	
    return 0;
}
