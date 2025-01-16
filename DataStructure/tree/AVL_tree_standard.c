#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct students {
    struct students* llink;
    struct students* rlink;

    char id[10];    // 학번
    char dep[20];   // 학과
    char name[10];  // 이름
    char blood[5];  // 혈액형
    int grade;      // 학년
    double height;  // 키
    double weight;  // 몸무게
    int nodeHeight; // 노드 높이
} stu;

//노드 높이 및 균형 계신
int getHeight(stu* node) {
    return node ? node->nodeHeight : 0;
}

int getBalanceFactor(stu* node) {
    return node ? getHeight(node->llink) - getHeight(node->rlink) : 0;
}

// 오른쪽 회전 (LL 불균형 해결)
stu* rotateRight(stu* y) {
    stu* x = y->llink; // y의 왼쪽 자식을 새로운 루트로 설정
    stu* T = x->rlink; // x의 오른쪽 서브트리를 임시로 저장

    // 회전 과정
    x->rlink = y;      // x의 오른쪽 자식으로 y를 설정
    y->llink = T;      // y의 왼쪽 자식으로 T를 설정

    // 노드 높이 재계산
    y->nodeHeight = 1 + (getHeight(y->llink) > getHeight(y->rlink) ? getHeight(y->llink) : getHeight(y->rlink));
    x->nodeHeight = 1 + (getHeight(x->llink) > getHeight(x->rlink) ? getHeight(x->llink) : getHeight(x->rlink));

    return x; // 새로운 루트를 반환
}

// 왼쪽 회전 (RR 불균형 해결)
stu* rotateLeft(stu* x) {
    stu* y = x->rlink; // x의 오른쪽 자식을 새로운 루트로 설정
    stu* T = y->llink; // y의 왼쪽 서브트리를 임시로 저장

    // 회전 과정
    y->llink = x;      // y의 왼쪽 자식으로 x를 설정
    x->rlink = T;      // x의 오른쪽 자식으로 T를 설정

    // 노드 높이 재계산
    x->nodeHeight = 1 + (getHeight(x->llink) > getHeight(x->rlink) ? getHeight(x->llink) : getHeight(x->rlink));
    y->nodeHeight = 1 + (getHeight(y->llink) > getHeight(y->rlink) ? getHeight(y->llink) : getHeight(y->rlink));

    return y; // 새로운 루트를 반환
}


stu* insertNode(stu* root, stu* data) {
    if (root == NULL) {
        stu* newNode = (stu*)malloc(sizeof(stu));
        newNode->llink = NULL;
        newNode->rlink = NULL;

        strcpy(newNode->id, data->id);
        strcpy(newNode->dep, data->dep);
        strcpy(newNode->name, data->name);
        strcpy(newNode->blood, data->blood);
        newNode->grade = data->grade;
        newNode->height = data->height;
        newNode->weight = data->weight;
        newNode->nodeHeight = 1;

        return newNode;
    }

    if (strcmp(data->id, root->id) < 0) {
        root->llink = insertNode(root->llink, data);
    }
    else if (strcmp(data->id, root->id) > 0) {
        root->rlink = insertNode(root->rlink, data);
    }
    else {
        printf("같은 값 입력은 불가능합니다.\n");
        return root;
    }

    root->nodeHeight = 1 + (getHeight(root->llink) > getHeight(root->rlink) ? getHeight(root->llink) : getHeight(root->rlink));

    int balanceFactor = getBalanceFactor(root);

    // LL Case
    if (balanceFactor > 1 && strcmp(data->id, root->llink->id) < 0) {
        return rotateRight(root);
    }

    // RR Case
    if (balanceFactor < -1 && strcmp(data->id, root->rlink->id) > 0) {
        return rotateLeft(root);
    }

    // LR Case
    if (balanceFactor > 1 && strcmp(data->id, root->llink->id) > 0) {
        root->llink = rotateLeft(root->llink);
        return rotateRight(root);
    }

    // RL Case
    if (balanceFactor < -1 && strcmp(data->id, root->rlink->id) < 0) {
        root->rlink = rotateRight(root->rlink);
        return rotateLeft(root);
    }

    return root;
}

void printTree_1(stu* root) {
    if (root != NULL) {
        printTree_1(root->llink);
        printf("\nID: %s, 학과: %s, 이름: %s, 학년: %d, 키: %.2f, 몸무게: %.2f",
            root->id, root->dep, root->name, root->grade, root->height, root->weight);
        printTree_1(root->rlink);
    }
}

void printTree_2(stu* root) {
    if (root != NULL) {
        printTree_2(root->rlink);
        printf("\nID: %s, 학과: %s, 이름: %s, 학년: %d, 키: %.2f, 몸무게: %.2f",
            root->id, root->dep, root->name, root->grade, root->height, root->weight);
        printTree_2(root->llink);
    }
}

stu* searchTree(stu* root, const char* id) {
    if (root == NULL) {
        printf("학생 정보를 찾을 수 없습니다.\n");
        return NULL;
    }

    if (strcmp(id, root->id) < 0) {
        return searchTree(root->llink, id);
    }
    else if (strcmp(id, root->id) > 0) {
        return searchTree(root->rlink, id);
    }
    else {
        printf("학생 정보를 찾았습니다: ID: %s, 이름: %s, 학과: %s, 학년: %d, 키: %.2f, 몸무게: %.2f\n",
            root->id, root->name, root->dep, root->grade, root->height, root->weight);
        return root;
    }
}

stu* findMin(stu* node) {
    while (node->llink != NULL) {
        node = node->llink;
    }
    return node;
}

stu* deleteNode(stu* root, const char* id) {
    if (root == NULL) {
        printf("삭제할 학생 정보를 찾을 수 없습니다.\n");
        return NULL;
    }

    if (strcmp(id, root->id) < 0) {
        root->llink = deleteNode(root->llink, id);
    }
    else if (strcmp(id, root->id) > 0) {
        root->rlink = deleteNode(root->rlink, id);
    }
    else {
        // 노드 발견
        if (root->llink == NULL || root->rlink == NULL) {
            stu* temp = root->llink ? root->llink : root->rlink;
            free(root);
            printf("학생 정보가 성공적으로 삭제되었습니다.\n");
            return temp;
        }

        stu* temp = findMin(root->rlink);
        strcpy(root->id, temp->id);
        strcpy(root->dep, temp->dep);
        strcpy(root->name, temp->name);
        strcpy(root->blood, temp->blood);
        root->grade = temp->grade;
        root->height = temp->height;
        root->weight = temp->weight;
        root->rlink = deleteNode(root->rlink, temp->id);
    }

    root->nodeHeight = 1 + (getHeight(root->llink) > getHeight(root->rlink) ? getHeight(root->llink) : getHeight(root->rlink));
    int balanceFactor = getBalanceFactor(root);

    // LL Case
    if (balanceFactor > 1 && getBalanceFactor(root->llink) >= 0) {
        return rotateRight(root);
    }

    // LR Case
    if (balanceFactor > 1 && getBalanceFactor(root->llink) < 0) {
        root->llink = rotateLeft(root->llink);
        return rotateRight(root);
    }

    // RR Case
    if (balanceFactor < -1 && getBalanceFactor(root->rlink) <= 0) {
        return rotateLeft(root);
    }

    // RL Case
    if (balanceFactor < -1 && getBalanceFactor(root->rlink) > 0) {
        root->rlink = rotateRight(root->rlink);
        return rotateLeft(root);
    }

    return root;
}


int menu() {
    int code;
    while (1) {
        printf("\n----------------------------------");
        printf("\n  학생 정보 관리 프로그램 AVL 트리 ");
        printf("\n----------------------------------");
        printf("\n 1. 학생 정보 입력 ");
        printf("\n 2. 학생 정보 출력(오름차순) ");
        printf("\n 3. 학생 정보 출력(내림차순) ");
        printf("\n 4. 검색할 학생 정보 : ");
        printf("\n 5. 삭제할 학생 정보 : ");
        printf("\n 6. 프로그램 종료 : ");

        printf("\n---------------------------");
        printf("\n 메뉴를 입력 : ");

        if (scanf("%d", &code) == 1 && code >= 1 && code <= 6) {
            return code;
        }
        else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            while (getchar() != '\n');
        }
    }
}

int main() {
    int code;
    stu* root = NULL;
    stu* data = (stu*)malloc(sizeof(stu));

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
            scanf("%lf", &data->height);

            printf("몸무게를 입력하세요 : ");
            scanf("%lf", &data->weight);

            root = insertNode(root, data);
        }
        else if (code == 2) {
            printTree_1(root);
        }
        else if (code == 3) {
            printTree_2(root);
        }
        else if (code == 4) {
            char searchId[10];
            printf("검색할 학생의 학번을 입력하세요: ");
            scanf("%s", searchId);
            searchTree(root, searchId);
        }
        else if (code == 5) {
            char deleteId[10];
            printf("삭제할 학생의 학번을 입력하세요: ");
            scanf("%s", deleteId);
            root = deleteNode(root, deleteId);
        }
        else if (code == 6) {
            break;
        }
    }

    free(data);
    return 0;
}
