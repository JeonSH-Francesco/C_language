#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10

main(){
    int values[size];
    int i,max,min;

    srand((unsigned int)time(NULL));

    for(i=0;i<size;i++){
    values[i]=rand()%100;

    if(i!=size-1){
    printf("%d, ",values[i]);
    }

    else{
        printf("%d",values[i]);
    }

    }
    printf("\n");

    max=values[0];
    min=values[0];

    for(i=1;i<size;i++){
        if(values[i]>max)
        max=values[i];
        if(values[i]<min)
        min=values[i];

    }

    printf("Max: %d min: %d ",max,min);
    return 0;
}
