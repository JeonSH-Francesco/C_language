#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 180000
#define MAX_WORD_LENGTH 200
#define MAX_ADDWORD_LENGTH 2200

typedef struct MyStruct {
    char word[MAX_WORD_LENGTH];
    char addword[200]; // 동적 할당을 위한 포인터
} dictionary;

int main() {
    dictionary* word_db;
    word_db = (dictionary*)malloc(sizeof(dictionary) * MAX_WORDS);

    int inputnum = 0;
    
    

    FILE* fp = fopen("D:\\dictionary.txt", "a+");
    if (fp == NULL)
    {
        printf("file error~!\n");
        return 0;
    }



    while (inputnum != 5)
    {
        //1번과 관련된 변수
        int word_leng = 0;
        int i = 0;
        int left = 0, right = 0, max = 0, max_index = 0, count = 0;
        char word[MAX_ADDWORD_LENGTH];
        //2번과 관련된 변수
        int line_num = 0; int is_end = 0;
       
        printf("전자사전 프로그램\n");
        printf("----------------------------\n");
        printf("1. 사전 단어 갯수 확인\n");
        printf("2. 단어 검색\n");
        printf("3. 단어 추가\n");
        printf("4. 단어 삭제\n");
        printf("5. 프로그램 종료\n");
        printf("----------------------------\n");
        printf("메뉴 선택: ");
        scanf("%d", &inputnum);



        if (inputnum == 1) {
            while (fgets(word, 2200, fp) != NULL) {
                word_leng = strlen(word);    //단어 길이 확인

                //공백 문장 처리 및 알파벳 아닌 것 처리
                if (word_leng <= 1 || (word[0] < 'A' || word[0] > 'z')) {
                    continue;
                }

                for (i = 0; i < word_leng; i++) {
                    if (word[i] == '(') {
                        left = i;
                    } //단어의 끝 인덱스 확인
                    if (word[i] == ')') {
                        right = i + 1;
                        break;
                    }//두번째 괄호 확인
                }
                //단어를 ( 전까지 읽은 것에 대한 -1을 한 것이 max 즉, 지금까지 읽은 가장 긴 단어
                if (i > max) {
                    max = i - 1;
                    max_index = count;
                }
                count++;
            }

            printf("\n단어 읽기 완료!! 총 %d개의 단어, 가장 긴 단어의 인덱스: %d, 단어의 길이는 %d입니다. \n\n", count, max_index, max);
            fseek(fp, 0, SEEK_SET);
        }


        if (inputnum == 2) {
            printf("검색할 단어를 입력하시오: ");
            scanf("%s", word_db->word);

            fseek(fp, 0, SEEK_SET);

            while (fgets(word, 2200, fp) != NULL) {
                line_num++;
                if (strstr(word, word_db->word)) {
                    printf("%d줄에서  %s가(이)발견되었습니다.\n", line_num, word_db->word);
                    is_end = 1;
                }
            }
            // is_end 감소를 없애고, line_num 초기화
            line_num = 0;

            if (is_end == 0) {
                printf("찾는 단어가 없습니다.\n");
            }

            fseek(fp, 0, SEEK_SET);

            printf("\n");
        }

        if (inputnum == 3) {
            // 키보드로부터 데이터 입력
            printf("추가할 단어를 입력하세요:");
            getchar(); // Enter key 처리
            fgets(word_db->addword, sizeof(word_db->addword), stdin);
            word_db->addword[strcspn(word_db->addword, "\n")] = '\0';

            // cmd창에 추가한 단어 표시
            fprintf(stdout, "%s\n", word_db->addword);

            // dictionary.txt 파일에 출력
            fprintf(fp, "%s\n", word_db->addword);
            printf("\n");
        }
        if (inputnum == 4) {
            printf("검색할 단어를 입력하시오: ");
            scanf("%s", word_db->word);

            int line_number = 0;
            int word_deleted = 0;

            while (fgets(word, 2200, fp) != NULL) {
                line_number++;
                char* word_position = strstr(word, word_db->word);
                char* parenthesis_position = strstr(word, "(");

                if (word_position != NULL && (parenthesis_position == NULL || word_position < parenthesis_position)) {
                    // 단어가 발견되고, ( 이전에 있는 경우에만 출력
                    printf("'%s'가 %d번째 줄에서 발견되었습니다.\n", word_db->word, line_number);
                    word_deleted = 1;

                    //fseek(fp, -strlen(word_db->index), SEEK_CUR); // 찾은 위치로 포인터 이동
                    fseek(fp, -(long)strlen(word), SEEK_CUR); // 찾은 위치로 포인터 이동
                    //fp=fseek(fp,-(long)strlen(word),fp);
                    // 삭제 대상 단어를 덮어쓰기
                    for (int i = 0; i < strlen(word); i++) {
                        fputc('-', fp);
                    }

                    fseek(fp, 0, SEEK_END); // 파일의 끝으로 이동하여 추가 입력을 방지
                }
            }

            if (!word_deleted) {
                printf("'%s' 단어를 찾지 못했습니다.\n", word_db->word);
            }
            else {
                printf("'%s' 단어가 삭제되었습니다.\n", word_db->word);
            }

            fseek(fp, 0, SEEK_SET);
            printf("\n");
        }
        /*if (inputnum == 4) {
            char choice = NULL;
            int del_choice = 0;
            FILE* fp = fopen("dictionary.txt", "r+");
            printf("삭제할 단어를 입력하세요:");
            scanf("%s", word_db->word);


            while (!(feof(fp))) {
                fgets(word, 2200, fp);
                word_leng = strlen(word);

                for (i = 0; i < word_leng; i++) {
                    if (word[i] == '(')
                    {
                        left = i;
                    } //단어의 끝 인덱스 확인
                    if (word[i] == ')')
                    {
                        right = i + 1; break;
                    }//두번째 괄호 위치의 인덱스 확인

                }
                line_num++;

                if (strstr(word, word_db->word)) {
                    printf("%d줄에서  %s가(이)발견되었습니다.\n", line_num, word_db->word);
                    is_end = 1;
                    del_choice = 1;
                }

            }//inputnum==4에서의 while문 끝나는 곳

            if (del_choice == 1) {
                printf("정말로 삭제하려는 단어를 삭제하시겠습니까?(Y or N):");
                scanf("%s", &choice);

                if (choice == 'Y') {
                    fseek(fp, -word_leng, SEEK_CUR);  //삭제할 위치의 포인터를 이동시켜서 그 이후부터 -로 덮어버린다.
                    printf("-를 입력하여 삭제하시오!");
                    fscanf(stdin, "%s", word_db->word);
                    fprintf(fp, "%s", word_db->word);
                }

                else
                    break;
            }
            is_end--;

            if (is_end != 0) {//printf("%d",is_end);
                printf("삭제하려는 단어가 없습니다.\n");
            }

            line_num = 0;
            fseek(fp, 0, SEEK_SET);

            printf("\n");



        }*/



    }


    fclose(fp);
    free(word_db);


}
