#include <stdio.h>
#include <stdlib.h>
#include <time.h>

main(){
    /*�н������� ����*/
    unsigned short int length=8;
    /*rand()�� �õ尪 ����*/
    srand((unsigned int)time(NULL));


    while(length--){
        putchar(rand()%94+33);//�ƽ�Ű�ڵ� 33�� ���� 126������
        srand(rand());
    }
    printf("\n");

    return 0;


}
