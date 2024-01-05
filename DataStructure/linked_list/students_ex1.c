#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStruct
{
    char id[20];
    char dep[20];
    char name[20];
    char blood[5];
    int grade;
    float height;
    float weight;

    struct students* next;

}students;

int menu() {
    int code = 0;
    printf("학생 정보 관리 프로그램\n");
    printf("\n----------------------------------------------------");
    printf("\n 1. 학생 정보 입력");
    printf("\n 2. 학생 정보 삭제");
    printf("\n 3. 학생 검색");
    printf("\n 4. 학생 정보 출력");
    printf("\n 5. 프로그램 종료");
    printf("\n----------------------------------------------------\n");
    printf("메뉴선택: ");
    scanf("%d", &code);
    return code;
}

students* load_db() {

    int count = 0;
    students* new_Node = NULL;
    students* head = NULL;
    students* temp = NULL;

    FILE* fp = fopen("st_db.txt", "rt");

    while (!feof(fp)) {
        //메모리 heap영역에 students 정보 1명 저장 가능한 메모리 할당
        //첫번째 주소를 반환
        new_Node = (students*)malloc(sizeof(students));
        new_Node->next = NULL; //노드를 만들면 반드시 초기화 필요

        fscanf(fp, "%s", new_Node->id);
        fscanf(fp, "%s", new_Node->dep);
        fscanf(fp, "%s", new_Node->name);
        fscanf(fp, "%s", new_Node->blood);
        fscanf(fp, "%d", &(new_Node->grade));
        fscanf(fp, "%f", &(new_Node->height));
        fscanf(fp, "%f", &(new_Node->weight));


        if (head == NULL) {
            head = new_Node;
        }
        else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_Node;
        }

        count++;
    }
    printf("현재 DB에는 %d명의 학생이 있습니다.\n", count);
    fclose(fp);

    return head;
}

//학번 중복 체크 함수
int isDuplicate(students* head, const char* id) {
    students* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            printf("중복된 학번입니다.\n");
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

students* input_db(students* head) {
    students* temp = head;
    students* new_Node = NULL;
    students* prev = NULL;
    students* next = NULL;

    new_Node = (students*)malloc(sizeof(students));
    if (!new_Node) {
        printf("메모리 할당에 실패했습니다.\n");
        return head;
    }
    new_Node->next = NULL;

    printf("\n학번: ");
    scanf("%s", new_Node->id);

    if (isDuplicate(head, new_Node->id)) {
        printf("이미 존재하는 학번입니다. 입력을 취소합니다.\n");
        free(new_Node);
        return head;
    }

    printf("\n학과: ");
    scanf("%s", new_Node->dep);

    printf("\n이름: ");
    scanf("%s", new_Node->name);

    printf("\n혈액형: ");
    scanf("%s", new_Node->blood);

    printf("\n학년: ");
    scanf("%d", &(new_Node->grade));

    printf("\n키: ");
    scanf("%f", &(new_Node->height));

    printf("\n몸무게: ");
    scanf("%f", &(new_Node->weight));


    if (head == NULL) {
        head = new_Node;
    }

    else {
        temp = head;
        while ((strcmp(new_Node->id, temp->id) > 0) && (temp->next != NULL)) {
            prev = temp;
            next = temp->next;
            temp = temp->next;
        }
        //처음
        if (temp == head)
        {
            head = new_Node;
            new_Node->next = temp;
        }
        //중간
        else if (temp->next != NULL)
        {
            prev->next = new_Node;
            new_Node->next = temp;
        }
        else if (temp->next == NULL)
        {
            temp->next = new_Node;
            new_Node->next = NULL;
        }

    }

    return head;
}


students* delete_db(students* head) {
    students* temp = head;
    students* prev = NULL;
    students* data = (students*)malloc(sizeof(students)); // Allocate memory for data
    FILE* fp = fopen("st_db.txt", "r+");

    if (fp == NULL) {
        printf("File open error.\n");
        return head;
    }

    printf("\n삭제할 학생이름: ");
    scanf("%s", data->name);

    while (temp != NULL) {
        if (strcmp(temp->name, data->name) == 0) {

            if (prev == NULL) {
                head = temp->next;
            }
            else {
                prev->next = temp->next;
            }

            //초기화
            fseek(fp, 0, SEEK_SET);

            //삭제할 데이터는 제외하고 갱신
            students* current = head;

            while (current != NULL) {
                fprintf(fp, "\n%s %s %s %s %d %.2f %.2f", current->id, current->dep, current->name, current->blood, current->grade, current->height, current->weight);
                current = current->next;
            }

            fclose(fp);
            free(temp);
            free(data);
            return head;
        }

        prev = temp;
        temp = temp->next;
    }

    fclose(fp);
    printf("\n%s의 학생정보가 없습니다.\n", data->name);
    free(data); // Free allocated memory
    return head;
}



int search_db(students* head) {
    students* temp = head, data;
    int index;
    printf("\n검색할 학생이름: ");
    scanf("%s", data.name);

    while (temp != NULL) {
        if (strcmp(temp->name, data.name) == 0) {
            printf("\n%s %s %s %s %d %.2f %.2f\n", temp->id, temp->dep, temp->name, temp->blood, temp->grade, temp->height, temp->weight);
            index = 1;
            return index;

        }
        temp = temp->next;
    }

    if (temp == NULL)
    {
        index = -1;
        printf("\n%s의 학생정보가 없습니다.\n", data.name);
        return index;
    }


}


int print_db(students* head) {

    int count = 0;
    students* temp;

    temp = head;


    while (temp != NULL) {
        printf("\n%s %s %s %s %d %.2f %.2f", temp->id, temp->dep, temp->name, temp->blood, temp->grade, temp->height, temp->weight);
        temp = temp->next;
        count++;
    }
    printf("\n현재 %d명이 있습니다.", count);

    printf("\n");
}

int exit_pgm(students* head) {
    int count = 0;
    students* temp = head;
    FILE* fp = fopen("st_db.txt", "wt");

    while (temp != NULL)
    {
        fprintf(fp, "\n%s %s %s %s %d %.2f %.2f", temp->id, temp->dep, temp->name, temp->blood, temp->grade, temp->height, temp->weight);
        temp = temp->next;
        count++;
    }

    printf("\n현재 %d명이 있습니다.", count);
    fclose(fp);
    exit(1);
}



void main() {
    students* head = NULL;
    students* temp;
    int code = 0, cnt = 0;
    int index=0;
    head = load_db();//프로그램 시작 시 st_db.txt 파일의 정보를 읽어 들여 첫번째 주소를 리턴~!

    print_db(head);

    while (1) {
        code = menu();
        printf("\n선택한 메뉴: %d\n", code);

        switch (code) {
        case 1: head = input_db(head); break;
        case 2: head = delete_db(head); break;
        case 3: search_db(head); break;
        case 4: print_db(head); break;
        case 5: exit_pgm(head); break;
        default: break;

        }

    }

}
