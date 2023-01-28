/*
삭제 부분 구현 잘 안되었고, 뭔가 수정이 더 필요함.
솔직히 말하면 정신건강에 안좋음.
->Neet to be fixed. Help your Advice!!!


dictionary.txt : https://drive.google.com/file/d/1lixBlIEVpIQ8Y6ceXRc8-AfTn05UZMRo/view?usp=share_link

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStruct{
    char word[200];
    char addword[50];
}dictionary;


int main(){
    dictionary *word_db;
    word_db = (dictionary*)malloc(sizeof(dictionary)*180000);


    int inputnum;
    //1번과 관련된 변수
    char word[2200]=" ";
    int i=0, left=0, right=0, max=0, max_index=0,count=0, word_leng;
    //2번과 관련된 변수
    int line_num; int is_end=0;
    //3번과 관련된 변수
     char bracket[10];//괄호안에 품사를 써넣는 배열
    //4번과 관련된 변수
    char del[1];
    int del_choice;
    char choice;

    FILE *fp= fopen("dictionary.txt","r");
    if (fp ==NULL)
    {
        printf("file error~!\n");
        return 0;
    }

    while(inputnum !=5)
    {
        printf("전자사전 프로그램\n");
        printf("----------------------------\n");
        printf("1. 사전 단어 갯수 확인\n");
        printf("2. 단어 검색\n");
        printf("3. 단어 추가-> 메뉴선택에 추후 단어,품사,정의 순으로 입력 바람\n");
        printf("4. 단어 삭제\n");
        printf("5. 프로그램 종료\n");
        printf("----------------------------\n");
        printf("메뉴 선택: ");
        scanf("%d",&inputnum);


        if(inputnum==1){
        while(!feof(fp))
        {
        fgets(word,2200,fp); //한줄씩 읽기
        word_leng =strlen(word);    //단어 길이 확인
        if(word_leng<=1) continue; //공백 문장 처리
        if(word[0]<'A'||word[0]>'z') //알파벳이 아닌 것 처리
            continue;

        for(i=0;i<word_leng;i++){
            if(word[i]=='(')
            {left=i;} //단어의 끝 인덱스확인
            if(word[i]==')')
            {right=i+1; break;}//두번째 괄호 확인
        }
        //단어를 ( 전까지 읽은 것에 대한 -1을 한것이 max 즉, 지금까지 읽은 가장 긴 단어
        if(i>max){
            max=i-1;
            max_index=count;
        }
        count++;
        }


        printf("\n단어 읽기 완료!! 총 %d개의 단어, 가장 긴 단어의 인덱스: %d, 단어의 길이는 %d입니다. \n\n", count,max_index,max);

        }



    if(inputnum==2){
         printf("검색할 단어를 입력하시오: ");
         scanf("%s",word_db->word);


        while(fgets(word,2200,fp)){
        line_num++;
        if(strstr(word,word_db->word))
            { printf("%d줄에서  %s가(이)발견되었습니다.\n",line_num,word_db->word);
               is_end=1;
            }
        }
        is_end--;
        //printf("%d",is_end);

        if(is_end!=0){//printf("%d",is_end);
        printf("찾는 단어가 없습니다.\n");}

        line_num=0;
        fseek(fp,0,SEEK_SET);

        printf("\n");

        }


    if(inputnum==3){

     FILE *fp;
    char buffer[50];

    fp=fopen("dictionary.txt","a+");


    fgets(buffer,sizeof(buffer),stdin);
    fputs(buffer,fp);

    fseek(fp,0,SEEK_SET);
    printf("\n");

    }

    if(inputnum==4){
        FILE *fp= fopen("dictionary.txt","r+");
        printf("삭제할 단어를 입력하세요:");
        scanf("%s",word_db->word);


        while(!(feof(fp))){
            fgets(word,2200,fp);
            word_leng =strlen(word);

            for(i=0;i<word_leng;i++){
            if(word[i]=='(')
            {left=i;} //단어의 끝 인덱스 확인
            if(word[i]==')')
            {right=i+1; break;}//두번째 괄호 위치의 인덱스 확인

            //printf("\n%s\n",word);//맨 마지막 단어
            // printf("\n%d\n",left); //맨 마지막 단어의 ( 가 나오는 인덱스
            //printf("\n%d\n",right);//맨 마지막 단어의 ) 가 나오는 인덱스
            }
            line_num++;

            if(strstr(word,word_db->word)){
                printf("%d줄에서  %s가(이)발견되었습니다.\n",line_num,word_db->word);
                is_end=1;
                del_choice=1;
            }

            }//inputnum==4에서의 while문 끝나는 곳

            if(del_choice==1){
            printf("정말로 삭제하려는 단어를 삭제하시겠습니까?(Y or N):");
            scanf("%s",&choice);

            if(choice=='Y'){
                fseek(fp,-word_leng,SEEK_CUR);  //삭제할 위치의 포인터를 이동시켜서 그 이후부터 -로 덮어버린다.
                printf("-를 입력하여 삭제하시오!");
                fscanf(stdin,"%s",word_db->word);
                fprintf(fp,"%s",word_db->word);
            }

            else
                break;
            }
            is_end--;

            if(is_end!=0){//printf("%d",is_end);
            printf("삭제하려는 단어가 없습니다.\n");}

            line_num=0;
            fseek(fp,0,SEEK_SET);
            printf("\n");

    }

}

fclose(fp);
free(word_db);


}
