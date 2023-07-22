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
/*
#include <stdio.h>

int main(){
    int i=0;
    int j=0;

    for(i=0;i<3;i++){
        for(j=i;j<3;j++){
            printf("*");
        }
        printf("\n");
    }

    int k=0;
    int l=0;
    
    while(l<3){
        l++;
        k=3;
        //printf("l=%d",l);
        while(k>=l){
            k--;
            //printf("k= %d",k);
            printf("*");

        }
        printf("\n");
    }

}
*/
