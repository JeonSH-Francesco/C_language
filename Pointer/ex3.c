#include <stdio.h>

 int main(void){

    int i;
    int array1[8]={1,2,3,4,5,6,7,8};
    int array2[8];

    printf("실행 전:");
    for(i=0;i<8;i++)
        {printf("%d ",array1[i]);
            if(i<7)
            {array2[i+1]=array1[i];}
            else
            {array2[0]=array1[7];}}
    printf("\n실행 후:");
    for(i=0;i<8;i++)
        {printf("%d ",array2[i]);}

 }
 /*#include <stdio.h>
void arrayshift(int *p);

int main(){
    int array1[8]={1,2,3,4,5,6,7,8};
    int i;
    printf("실행 전:");
    for(i=0;i<8;i++)
        printf("%d ",array1[i]);
    printf("\n");

    arrayshift(array1);
    printf("실행 후:");
    for(i=0;i<8;i++)
        printf("%d ",array1[i]);
    printf("\n");

    return 0;
}
void arrayshift(int *p){
    int i,temp;
    temp=p[7];
    for(i=7;i>0;i--)
        p[i]=p[i-1];
    p[0]=temp;
}
*/
