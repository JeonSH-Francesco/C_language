#include <stdio.h>

int main(void){
    int array[3]={10,20,30};

    printf("array [0] address is array's name : %x %x %x\n",array,array+0, &array[0]);
    printf("array [1] address :%x %x\n",array+1, &array[1]);
    printf("array [2] address :%x %x\n",array+2, &array[2]);

    printf("%d %d %d\n",sizeof(array),sizeof(array+0),sizeof(&array[0]));

    return 0;
}

----------------
  #include <stdio.h>

int main(void){
    int array[3]={10,20,30};
    int i=0;
    int *p =NULL;

    p = array;

    for(i=0;i<3;i++){
        printf("%d %d %d \n",*(p+i),*&p[i], p[i]);

    }
    printf("=====================\n");
    for(i=0;i<3;i++){
        printf("%d %d %d \n",*(array+i),*&array[i], array[i]);

    }

    return 0;
}
--------------
#include <stdio.h>

int main() {
	int arr[5] = { 2,4,6,8,10 };
	int *p = arr;
	int num = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
				num = *(p + 1 + j);
				*(p + 1 + j) = *(p + j);
				*(p + j) = num;
		}
	}

	for (int i = 0; i < 5; i++) {
		printf("%d \n", p[i]);
	}

	return 0;
}
