#include <stdio.h>

int main(void){
    char array[]={'A','B','C','D'};

    //문자 상수
    printf("%c %c %c %c\n",array[0],array[1],array[2],array[3]);

    array[0]='D';
    array[1]='C';
    array[2]='B';
    array[3]='A';

    printf("%c %c %c %c\n",array[0],array[1],array[2],array[3]);

   return 0;
}
--------------
#include <stdio.h>

int main(void){
    char array[]={'A','B','C','D'};
    char array1[]="ABCD";
    char *cp="ABCD";
    char *p = NULL;
    p=array;

    for(int i=0;i<4;i++){
    printf("%c",p[i]);
    }
    printf("\n");

    for(int i=0;i<4;i++){
    printf("%c",*(p+i));
    }

    printf("\n");
    for(int i=0;i<4;i++){
    printf("%s\n",array1+i);
    }

    printf("\n");
    for(int i=0;i<4;i++){
    printf("%s\n",cp+i);
    }

   return 0;
}
-----------
#include <stdio.h>

int main(void){

    char *p ="Good morning";
    char *q ="C-language";
    char *array[2]={"Good morning","C-language"};

    printf("%s\n",p);
    printf("%s\n",q);
    printf("===============\n");

    printf("%s\n",array[0]);
    printf("%s\n",array[1]);
    printf("===============\n");

    printf("%s\n",p+5);
    printf("%s\n",q+2);
    printf("===============\n");

    printf("%s\n",array[0]+5);
    printf("%s\n",array[1]+2);
    printf("===============\n");

}
