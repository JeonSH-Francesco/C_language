#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main(){
    /*패스워드의 길이*/
    unsigned short int length=8;
    /*rand()의 시드값 설정*/
    srand((unsigned int)time(NULL));


    while(length--){
        putchar(rand()%94+33);//아스키코드 33번 부터 126번까지
        srand(rand());
    }
    printf("\n");

    return 0;


}
