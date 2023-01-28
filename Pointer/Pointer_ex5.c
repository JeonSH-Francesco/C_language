#include <stdio.h>

//pointer array declare
//For address save

int main(void){
    int a=1, b=2, c=3;
    int * pointer[3]={};
    int i=0;

    pointer[0]=&a;
    pointer[1]=&b;
    pointer[2]=&c;

    printf("a's address: 0x%x \nb's address: 0x%x \nc's address: 0x%x\n",pointer[0],pointer[1],pointer[2]);
    printf("a : %d b: %d c: %d",*pointer[0],*pointer[1],*pointer[2]);


    return 0;
}
------------
#include <stdio.h>
int main(void){
    int a=10,b=20,c=30;
    int *ap[3]={NULL,NULL,NULL}; //pointer array 포인터 배열은 주소값들을 저장하는 배열 이다

    int array[2][3]={10,20,30,40,50,60};
    int (*p)[3]=NULL; //array pointer 배열 포인터는 배열의 시작주소값을 저장할 수 있는 포인터

    ap[0]=&a;
    ap[1]=&b;
    ap[2]=&c;

    printf("a's address : 0x%x\nb's address: 0x%x\nc's address : 0x%x\n", &a, &b, &c);
    printf("------------------\n");
    printf("%x %x %x\n", ap[0], ap[1], ap[2]);
    printf("%x %x %x\n",*(ap+0),*(ap+1),*(ap+2));
    printf("------------------\n");
    /*
    ap[i]=*(ap+i)
    */

    printf("a's value : %d\nb's value : %d\nc's value :%d\n",*&a, *&b, *&c);
    printf("------------------\n");
    printf("%d %d %d\n",*ap[0],*ap[1],*ap[2]);
    printf("%d %d %d\n",**(ap+0),**(ap+1),**(ap+2));

    //배열 포인터 변수에 시작 주소를 저장
    //p는 3열짜리 2차원 배열의 주소를 저장할 수 있는 변수
    p=array;
    printf("------------------\n");
    printf("%d %d %d\n",p[0][0],p[0][1],p[0][2]);
    printf("%d %d %d\n",p[1][0],p[1][1],p[1][2]);
    printf("------------------\n");

    /*
    p[i]=*(p+i)
    */
    printf("%d %d %d\n",*(p[0]+0),*(p[0]+1),*(p[0]+2));
    printf("%d %d %d\n",*(p[1]+0),*(p[1]+1),*(p[1]+2));
    printf("------------------\n");

    printf("%d %d %d\n",*(*(p+0)+0),*(*(p+0)+1),*(*(p+0)+2));
    printf("%d %d %d",*(*(p+1)+0),*(*(p+1)+1),*(*(p+1)+2));

    return 0;
}
