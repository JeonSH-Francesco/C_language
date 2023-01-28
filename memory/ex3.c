#include <stdio.h>
#include <stdlib.h>


int main(void){
    int i=0;

    int *p=(int*)malloc(4);
    p[0]=10;
    p[1]=20;

    p=(int*)realloc(p,sizeof(int)*4);
    p[2]=30;
    p[3]=40;

    for(i=0;i<4;i++){
        printf("p[%d] : %d\n",i,p[i]);
    }
    free(p);
    p=NULL;

    return 0;
}
