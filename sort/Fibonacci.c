#include <stdio.h>
int sum(int x);//함수 선언부

int main(void){
    int i,k;

    printf("Input number: (1~46까지)");
    scanf("%d", &k);

    for(i=1;i<=k;i++)
    {
        printf("%d\n", sum(i)); //함수 호출부
    }
    printf("\n %d번째 피보나치 수열의 수는: %d입니다.",k,sum(i-1));
    printf("\n");
}
//int의 범위 -21억4748만3647 ~21억4748만3647
// 46번째 피보나치 수열의 수는: 18억3631만1903

//함수 선언부
int sum(int x){
    if (x<=2)
        return 1;
    else
        return sum(x-2)+sum(x-1);

}
