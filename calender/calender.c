#include <stdio.h>

int main(void){
    int year,month;       //년월 입력해서 날짜 확인
    int sum=0;            //1월1일 계산
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
                          //숫자 입력
    int i,j;              //루프 카운터
    int k;

    printf("Check YYYY MM:");
    scanf("%d  %d",&year, &month);

    //윤년 계산
    if((year%4==0)&&!(year%100==0)||(year%400==0))
     {day[1]++;}

    sum=365;

    for(i=1;i<year;i++){
         if((i%4==0)&&!(i%100==0)||(i%400==0))
            sum +=366;

        else
            sum +=365;
    }
    //윤달인 경우와 평년인 경우 sum을 다르게 더해서 sum의 값을 갱신

    //특정년도 특정 달까지의 sum의 계산 과정
    for(i=0;i<month-1;i++){
        sum+=day[i];
    }
    //k라는 변수를 이용하여 일주일 간격으로 시작되는 요일 초기화
    k= sum%7;

    //printf("%d\n",k);
    //printf("%d\n",sum);
    printf("\t\t%d\t%d\n",year,month);
    printf("  SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
    printf("===================================================\n");

    for(j=0;j<k;j++){
        printf("\t");
    }//k라는 변수 이용하여 들여쓰기 한 달력 setting하고

    for(i=1;i<=day[month-1];i++){

        {   if(i==1)printf("");
            if(i<10)printf(" ");}  //일수가 한자리수들(1-9) 보기 좋게 정렬한것!
        printf("%d\t", i);  //나머지 숫자 정리
        //printf("k:%d",k);
        if(k == 6){   //k는 0부터 6까지의 값을 가지는데 들여쓰기 한 k 부터 해서 일주일이 채워지면
            k = 0;
            printf("\n  "); //개행
            continue;
        }
        k++;

    }
    printf("\n");

}
