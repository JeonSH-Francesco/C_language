#include <stdio.h>

int main(){

    int i,j; //count int
    int num;

    printf("Input num : ");
    scanf("%d",&num);

    //j라는 변수가 입력한 숫자 num전까지 증가연산을 수행하면
    //i라는 변수는 소수의 정의에 의해
    //즉,소수는 1과 자신을 약수로 가지는 수이므로, i는 2부터 j까지 증가하면서
    //j를 i로 나누기 연산을 했을때 나머지가 0이면, i의 증가 연산을 멈추고 break문에 의해 빠져나오고
    //증가한 j와 i가 같으면 -->즉,1과 자기자신을 갖는 소수이면 i를 출력
    for(j=1;j<num;j++){
            //printf("j=%d ",j);
        for(i=2;i<j;i++){
            //printf("i=%d ",i);
            if(j%i==0)
                break;
        }
        if(i==j)
            printf("%d\n",i);
    }


    return 0;
}
