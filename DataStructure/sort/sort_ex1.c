#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#define SWAP(x,y,temp) ((temp)=(x),(x)=(y),(y)=(temp))
#define MAX(a,b) ((a>b) ? a:b)

typedef struct MyStruct {
    char word[100];
}gamedb;

typedef struct bTree
{
    struct btree* llink;
    char word[100];
    struct btree* rlink;
}btree;

/*bubble-------------------------*/
void bubble_sort(gamedb* db, int n) {
    int i = 0, j = 0;
    gamedb temp;
    //n은 단어의 갯수로 받고 swap명령
    for (i = n - 1; i > 0; i--) {
        for (j = 0; j < 1; j++) {
            if (strcmp(db[j].word, db[j + 1].word) > 0) {
                temp = db[j];
                db[j] = db[j + 1];
                db[j + 1] = temp;
            }
        }
    }

    return;
}

void save_bubble(gamedb* db, int title, int word_count) {
    char save_title[3][30] = { "bubble_1.txt","bubble_2.txt","bubble_3.txt" };

    clock_t start = clock();
    bubble_sort(db, word_count);
    clock_t end = clock();
    printf("\n 정렬 소요시간: %lf", (double)(end - start) / CLOCKS_PER_SEC);

    file_save(db, save_title[title - 1], word_count);

    return;
}

/*quick-------------------------*/
void quick_sort(gamedb* db, int left, int right) {
    if (left < right) {
        int q = partition(db, left, right); //pivot설정
        quick_sort(db, left, q - 1);
        quick_sort(db, q + 1, right);
    } //left와 right가 같아지는 순간까지 자르는 실행
}

void save_quick(gamedb* db, int title, int word_count) {
    char save_title[3][30] = { "quick_1.txt","quick_2.txt","quick_3.txt" };

    clock_t start = clock();
    quick_sort(db, 0, word_count);
    clock_t end = clock();
    printf("\n 정렬 소요시간: %lf", (double)(end - start) / CLOCKS_PER_SEC);

    file_save(db, save_title[title - 1], word_count);

    return;
}
/*merge-------------------------*/
void merge(gamedb* db, gamedb* sorted, int left, int middle, int right) {
    int i, j, k, t;
    i = left;
    j = middle + 1;
    k = left;

    while (i <= middle && j <= right) {
        if (strcmp(db[i].word, db[j].word) <= 0) {
            sorted[k] = db[i];
            i++;
        }
        else {
            sorted[k] = db[j];
            j++;
        }
        k++;
    }
    //양쪽부분에서 남은부분 처리과정
    if (i > middle)
    {
        for (t = j; t <= right; t++, k++)
        {
            sorted[k] = db[t];
        }
    }


    else {
        for (t = i; t <= middle; t++, k++)
        {
            sorted[k] = db[t];
        }
    }


    for (t = left; t <= right; t++)
    {
        db[t] = sorted[t];
    }


}
void merge_sort(gamedb* db, gamedb* sorted, int left, int right) {
    int middle;
    if (left < right) {
        middle = (left + right) / 2;
        merge_sort(db, sorted, left, middle);
        merge_sort(db, sorted, middle + 1, right);
        merge(db, sorted, left, middle, right);
    }//left랑 right랑 같아지는 순간까지(분할이 끝날때 까지)
}


void save_merge(gamedb* db, int title, int word_count) {
    gamedb* sorted = NULL;
    char save_title[3][30] = { "merge_1.txt","merge_2.txt","merge_3.txt" };
    sorted = (gamedb*)malloc(sizeof(gamedb) * word_count);

    clock_t start = clock();
    merge_sort(db, sorted, 0, word_count);
    clock_t end = clock();
    printf("\n 정렬 소요시간: %lf", (double)(end - start) / CLOCKS_PER_SEC);

    file_save(sorted, save_title[title - 1], word_count);

    return;
}
/*tree----*/

btree* insertNode(btree* root, btree* data) {
    btree* temp;
    btree* newNode;
    temp = root;

    if (root == NULL) {
        newNode = (btree*)malloc(sizeof(btree));
        newNode->llink = NULL;
        newNode->rlink = NULL;

        strcpy(newNode->word, data->word);

        root = newNode;
        temp = newNode;
    }
    else if (strcmp(root->word, data->word) > 0)
    {
        temp->llink = insertNode(temp->llink, data);
    }
    else if (strcmp(root->word, data->word) < 0)
    {
        temp->rlink = insertNode(temp->rlink, data);
    }

    else
    {
        //printf("같은 값 입력은 불가능합니다.\n");
        return temp;
    }

    return temp;
}

void file_save_btree(btree* root, FILE* fp_out)
{//오름차순 inorder방식-->root와 파일의 주소를 받은것
//재귀함수호출에서 파일을 저장하기 위해서 제귀 호출 바깥부분에 파일을 만들고
//안에서 파일을 저장하고
//재귀호출 끝나고 파일을 닫는다.---->핵심
    if (root != NULL) {
        file_save_btree(root->llink, fp_out);
        fprintf(fp_out, "%s\n", root->word);
        file_save_btree(root->rlink, fp_out);
    }
}

btree* btree_sort(gamedb* db, int word_count)
{
    int i = 0;
    btree* root = NULL;
    btree* data = NULL;
    data = (btree*)malloc(sizeof(btree));

    for (i = 0; i < word_count; i++)
    {
        strcpy(data->word, db[i].word);
        root = insertNode(root, data);
    }
    free(data);

    return root;
}//btree_sort가 끝나면 각 단어의 갯수만큼의 노드가 만들어지고 root 반환

void tree_free(btree* root)
{
    if (root != NULL) {
        tree_free(root->llink);
        tree_free(root->rlink);
        free(root);
    }
}

//노드가 순서대로 되어있지 않기에 file_save_btree함수 따로 만들어줘야함.
void save_btree(gamedb* db, int title, int word_count)
{
    char save_title[3][30] = { "btree_1.txt","btree_2.txt","btree_3.txt" };
    btree* root = NULL;

    clock_t start = clock();
    root = btree_sort(db, word_count);
    clock_t end = clock();
    printf("\n 정렬 소요시간: %lf", (double)(end - start) / CLOCKS_PER_SEC);

    FILE* fp_out = fopen(save_title[title - 1], "wt");
    file_save_btree(root, fp_out);
    fclose(fp_out);

    tree_free(root);

    return;
}
/*file_save-----------------------*/
int file_save(gamedb* db, char* title, int word_count) {
    int i = 0, not_save = 0, count = 0;

    FILE* fp_out = fopen(title, "wt");
    for (i = 0; i < word_count; i++)
    {
        for (int j = 0; j < strlen(db[i].word); j++)
            if (db[i].word[j] < 'A' || db[i].word[j]> 'z') {
                not_save = 1;
                break;
            }


        if (not_save != 1)
        {
            for (int j = i + 1; j < word_count; j++)
                if (strcmp(db[i].word, db[j].word) != 0)
                {
                    fprintf(fp_out, "%s %d \n", db[i].word, count + 1);
                    i = j - 1;
                    count = 0;
                    break;
                }
                else {

                    count++;
                }
            count = 0;
        }
        not_save = 0;
    }
    fclose(fp_out);

    printf("\n파일 저장 [%s] \n", title);
}

//메뉴설정
int menu() {
    int code = 0;
    printf("\n단어 정렬 프로그램");
    printf("\n------------------------------------");
    printf("\n1.정렬할 단어 파일 선택");
    printf("\n2.Bubble 정렬 후 저장");
    printf("\n3.Quick 정렬 후 저장");
    printf("\n4.Merge 정렬 후 저장");
    printf("\n5.이진트리 정렬 후 저장");
    printf("\n6.종료");
    printf("\n------------------------------------");
    printf("\n메뉴 선택 : ");
    scanf("%d", &code);

    return code;
}

int partition(gamedb* db, int left, int right)
{
    gamedb pivot, temp;
    int low, high, p;

    low = left;
    high = right + 1;
    p = (low + right) / 2;
    pivot = db[p];
    do {
        do {
            low++;
        } while (low <= right && strcmp(db[low].word, pivot.word) < 0);
        //오름차순일 경우 strcmp(a,b) 값이 음수이므로
        //왼쪽에 오름차순이 아닌 경우 while문 탈출 (low고정하고 분류작업)
        do {
            high--;
        } while (high >= left && strcmp(db[high].word, pivot.word) > 0);
        //오름차순이 아닐 경우 strcmp(a,b) 값이 양수이므로
        //오른족에 오름차순이 아닌 경우 while문 탈출 (high고정하고 분류작업)
        if (low < high) {
            SWAP(db[low], db[high], temp);
        }//pivot값보다 큰 경우 오른쪽 작은 경우 왼쪽
    } while (low < high);   //low와 right가 같아 질때까지

    SWAP(db[p], db[high], temp); //p=(left+right)/2로 설정한 이유는 정렬된 데이터를 다시 정렬할 필요가 없기 때문!!

    return high;
}




gamedb* load_file(char* title, int word_count)
{
    gamedb* db = NULL;
    int i = 0;

    db = (gamedb*)malloc(sizeof(gamedb) * word_count);
    printf("\n[%d] - 메모리할당", word_count);

    FILE* fp = fopen(title, "rt");
    while (!(feof(fp))) {
        fscanf(fp, "%s", db[i].word);
        i++;
    }

    fclose(fp);
    return db;
}


int check_file(char* title) {
    char word[100];
    int count = 0;
    FILE* fp = fopen(title, "rt");

    while (!feof(fp)) {
        fscanf(fp, "%s", word);
        count++;
    }
    printf("\n[%s]파일에는 [%d]개의 단어가 있습니다.", title, count);
    fclose(fp);

    return count;
}


gamedb* load_db(int* word_count, int* title) {
    gamedb* db = NULL;
    int menu = 0, chk_cnt = 0;
    char load_title[3][30] = { "1.txt","2.txt","3.txt" };


    do {
        printf("\n 어떤 파일로 게임을 시작할까요?");
        printf("\n 1.해리포터, 2.피터팬, 3.전쟁과평화");
        printf("\n----------------------------------");
        printf("\n메뉴:");
        scanf("%d", &menu);
    } while (menu < 1 || menu>3);

    chk_cnt = check_file(load_title[menu - 1]); //메뉴에서는 1,2,3으로 했기 때문
    //단어의 갯수 저장하고 파일도 정해지고 갯수만큼 메모리 할당해서 분류실행

    db = load_file(load_title[menu - 1], chk_cnt);
    *title = menu;
    *word_count = chk_cnt;
    return db;
}

int exit_game() {


}


void main() {
    gamedb* word_db = NULL;//주소형 변수 1개
    int code = 0, re = 0, word_count = 0, title = 0;// 게임에 사용할 단어의 개수 저장변수

    while (code != 6)
    {

        code = menu();

        switch (code) {
        case 1: word_db = load_db(&word_count, &title);
            break;
        case 2: save_bubble(word_db, title, word_count);
            break;
        case 3: save_quick(word_db, title, word_count);
            break;
        case 4: save_merge(word_db, title, word_count);
            break;
        case 5: save_btree(word_db, title, word_count);
            break;
        case 6: re = exit_game();
            break;
        }

    }

}
