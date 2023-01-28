#include <stdio.h>

void func(int (*p)[4],int num1, int num2);
//배열 포인터 변수를 p를 사용하여 접근하는 경우
int main(void){
    int array[2][4]={10,20,30,40,50,60,70,80};
    func(array,sizeof(array)/16,sizeof(array)/8);
    //시작주소, 행,열 이 변수로 들어감.
    return 0;
}

void func(int(*p)[4],int num1,int num2){
    int i,j;
    for(i=0;i<num1;i++){
        for(j=0;j<num2;j++){
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }

}
-----------
#include <stdio.h>

void func(int *p,int num);
//단일 포인터 변수를 p를 사용하여 접근하는 경우

int main(void){
    int array[2][4]={10,20,30,40,50,60,70,80};
    func(array,(sizeof(array)/16)*(sizeof(array)/8));
    return 0;
}

void func(int *p,int num){

for(int i=0;i<num;i++){
    printf("%d ",p[i]);
}

/*printf("%d",p[i][j]);꼴은 에러
이유는 단일 포인터 변수가 2차원 배열의 시작 주소를 저장해도 1차원 배열처럼 접근하기 때문
따라서 배열 포인터 변수로 변경하여 2차원 배열에 접근하여 함.
*/

}
