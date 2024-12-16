#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct students {
    struct students* llink;
    struct students* rlink;

    char id[10];    //학번
    char dep[20];   //학과
    char name[10];  //이름
    char blood[5];  //혈액형
    int grade;      //학년
    double height;  //키
    double weight;  //몸무게
} stu;

stu* insertNode(stu* root, stu* data) {
    stu* temp;
    stu* newNode;
    temp = root;

    if (root == NULL) {
        newNode = (stu*)malloc(sizeof(stu));
        newNode->llink = NULL;
        newNode->rlink = NULL;

        strcpy(newNode->id, data->id);
        strcpy(newNode->dep, data->dep);
        strcpy(newNode->name, data->name);
        strcpy(newNode->blood, data->blood);
        newNode->grade = data->grade;
        newNode->height = data->height;
        newNode->weight = data->weight;

        root = newNode;
        temp = newNode;
    }
    else if (strcmp(root->id, data->id) > 0) {
        root->llink = insertNode(root->llink, data);
    }
    else if (strcmp(root->id, data->id) < 0) {
        root->rlink = insertNode(root->rlink, data);
    }
    else {
        printf("같은 값 입력은 불가능합니다.");
        return root;
    }

    return root;
}

void printTree_1(stu* root) { // 오름 차순
    if (root != NULL) {
        printTree_1(root->llink); // 왼쪽 서브트리 탐색
        // 학번, 학과, 이름, 학년, 키, 몸무게 출력
        printf("\nID: %s, 학과: %s, 이름: %s, 학년: %d, 키: %.2f, 몸무게: %.2f",
            root->id, root->dep, root->name, root->grade, root->height, root->weight);
        printTree_1(root->rlink); // 오른쪽 서브트리 탐색
    }
}

void printTree_2(stu* root) { // 내림 차순
    if (root != NULL) {
        printTree_2(root->rlink); // 오른쪽 서브트리 탐색
        // 학번, 학과, 이름, 학년, 키, 몸무게 출력
        printf("\nID: %s, 학과: %s, 이름: %s, 학년: %d, 키: %.2f, 몸무게: %.2f",
            root->id, root->dep, root->name, root->grade, root->height, root->weight);
        printTree_2(root->llink); // 왼쪽 서브트리 탐색
    }
}

int searchTree(stu* root, stu* data) {
    stu* temp;
    temp = root;

    if (root == NULL) {
        return 0;
    }
    else if (strcmp(root->id, data->id) > 0) {
        return searchTree(temp->llink, data);
    }
    else if (strcmp(root->id, data->id) < 0) {
        return searchTree(temp->rlink, data);
    }
    else {
        printf("\n%s %s 학생을 찾았습니다~!!", temp->id, temp->name);
        return 1;
    }
}

stu* findMax(stu* root) { //최댓값을 가지는 노드 찾기
    while (root->rlink != NULL) {
        root = root->rlink;
    }
    return root;
}

stu* deleteNode(stu* root, stu* data) {
    if (root == NULL) {
        printf("정보가 없습니다.\n");
        return NULL;
    }

    if (strcmp(data->id, root->id) < 0) {
        root->llink = deleteNode(root->llink, data);
    }
    else if (strcmp(data->id, root->id) > 0) {
        root->rlink = deleteNode(root->rlink, data);
    }
    else {
        //자식 노드가 아예 없을 경우
        if (root->llink == NULL && root->rlink == NULL) {
            free(root);
            printf("삭제가 잘 진행되었습니다.");
            return NULL;
        }
        //자식노드가 2개 있는 경우
        else if (root->llink != NULL && root->rlink != NULL) {
            stu* maxNode = findMax(root->llink);
            strcpy(root->id, maxNode->id);
            strcpy(root->dep, maxNode->dep);
            strcpy(root->name, maxNode->name);
            strcpy(root->blood, maxNode->blood);
            root->grade = maxNode->grade;
            root->height = maxNode->height;
            root->weight = maxNode->weight;
            root->llink = deleteNode(root->llink, maxNode);
            printf("삭제가 잘 진행되었습니다.");
        }
        //자식 노드가 1개 있는 경우
        else {
            stu* child = (root->llink) ? root->llink : root->rlink;
            free(root);
            printf("삭제가 잘 진행되었습니다.");
            return child;
        }
    }
    return root;
}
int menu() {
    int code;
    int result; // to handle input validation

    while (1) {
        printf("\n----------------------------------");
        printf("\n  학생 정보 관리 프로그램 이진트리 ");
        printf("\n----------------------------------");
        printf("\n 1. 학생 정보 입력 ");
        printf("\n 2. 학생 정보 삭제 ");
        printf("\n 3. 학생 정보 검색 ");
        printf("\n 4. 학생 정보 출력(오름차순) ");
        printf("\n 5. 학생 정보 출력(내림차순) ");
        printf("\n 6. 종료 ");
        printf("\n---------------------------");
        printf("\n 메뉴를 입력 : ");

        result = scanf("%d", &code);

        
        if (result != 1 || code < 1 || code > 6) {
           
            while (getchar() != '\n');
            printf("잘못된 입력입니다. 1에서 6 사이의 숫자를 입력하세요.\n");
        }
        else {
            break;
        }
    }

    return code;
}

int main() {
    int code = 0, result = 0;
    stu* root = NULL;  //트리의 시작 주소를 저장하는 변수
    stu* data = (stu*)malloc(sizeof(stu));  //학생정보 저장 변수

    while (1) {
        code = menu();
        if (code == 1) {
            printf("학번을 입력하세요 : ");
            scanf("%s", data->id);

            printf("학과를 입력하세요 : ");
            scanf("%s", data->dep);

            printf("이름을 입력하세요 : ");
            scanf("%s", data->name);

            printf("혈액형을 입력하세요 : ");
            scanf("%s", data->blood);

            printf("학년을 입력하세요 : ");
            scanf("%d", &data->grade);

            printf("키를 입력하세요 : ");
            scanf("%lf", &data->height);  // 수정된 부분

            printf("몸무게를 입력하세요 : ");
            scanf("%lf", &data->weight);  // 수정된 부분

            root = insertNode(root, data);
        }
        if (code == 2) {
            printf("삭제할 학생의 학번을 입력하세요 : ");
            scanf("%s", data->id);
            root = deleteNode(root, data);
        }
        if (code == 3) {
            printf("찾을 학생 학번을 입력하세요 : ");
            scanf("%s", data->id);
            result = searchTree(root, data);
        }
        if (code == 4) printTree_1(root);
        if (code == 5) printTree_2(root);

        if (code == 6) break;
    }

    return 0;
}
