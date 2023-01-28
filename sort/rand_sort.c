#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main(){

    int ctr,inner,outer,didswap,temp;
    int nums[10];
    time_t t;

    //이 문장을 포함시키지 않으면 항상 동일 난수가 생성된다.
    srand(time(&t));

    for(ctr=0;ctr<10;ctr++)
    {
        nums[ctr]=(rand()%99)+1;
    }

    puts("정렬전의 리스트:");

    for(ctr=0;ctr<10;ctr++){
        printf("%d ",nums[ctr]);
    }
//정렬전에는 nums배열에 저장하여 출력하고
//정렬과정
    for(outer=0;outer<9;outer++){
        didswap=0;

        for(inner=outer;inner<10;inner++){
            //인덱스를  outer를 고정시키고 inner를 차례대로 증가시킨 후에 nums[inner]<nums[outer]
            //즉, 가장 큰 수를 뒤로 배열 시키는 과정(오름차순)
            if(nums[inner]<nums[outer]){

                temp=nums[inner];
                nums[inner]=nums[outer];
                nums[outer]=temp;

                didswap=1;//switch변수와 같은 것
            }
        }
        //오름차순이 유지가 되는 경우에는 할 필요가 없음.
        if(didswap==0){break;}

    }
    printf("\n");


    puts("정렬후의 리스트: ");
    for(ctr=0;ctr<10;ctr++)
    {
        printf("%d ",nums[ctr]);
    }

    printf("\n");
    return 0;

}
