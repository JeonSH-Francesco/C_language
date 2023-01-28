#include <stdio.h>
#include <stdlib.h>


int main(void){
    int i=0;
    int *p1=(int*)malloc(4);
    int *p2=(int*)calloc(sizeof(int),sizeof(int));

    printf("p1:%d\n",*p1);
    printf("p2:%d\n",*p2);

    free(p1);
    p1=NULL;

    free(p2);
    p2=NULL;

    return 0;
}
