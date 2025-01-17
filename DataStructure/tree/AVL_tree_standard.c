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


int getHeight(stu* node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return node->nodeHeight;
    }
}

int getBalanceFactor(stu* node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return getHeight(node->llink) - getHeight(node->rlink);
    }
}

// LL 회전 (오른쪽 회전)
stu* rotateRight(stu* parent) {
    stu* child = parent->llink;
    stu* temp = child->rlink;
    child->rlink = parent;
    parent->llink = temp;

    //부모 노드의 높이를 재계산
    //부모 기준으로 왼쪽 또는 오른쪽 자식노드가 있는 경우
    if (parent->llink != NULL || parent->rlink != NULL) {
        //부모 노드의 높이는 왼쪽 자식의 높이와 오른쪽 자식의 높이 중 큰 값에 1을 더하여 계산
        parent->nodeHeight = 1 + (getHeight(parent->llink) > getHeight(parent->rlink) ?
            getHeight(parent->llink) : getHeight(parent->rlink) );
    }
    else {
        //부모 기준으로 왼쪽, 오른쪽 자식노드가 없으면 높이는 1이다.
        parent->nodeHeight = 1;
    }

    //회전 완료 후 자식 노드의 높이를 재계산
    //자식 기준으로 왼쪽 또는 오른쪽 자식노드가 있는 경우 마찬가지로 계산
    if (child->llink != NULL || child->rlink != NULL) {
        child->nodeHeight = 1 + ( getHeight(child->llink) > getHeight(child->rlink) ? 
            getHeight(child->llink) : getHeight(child->rlink) );
    }
    else {
        child->nodeHeight = 1;
    }

    return child;
}

// RR 회전 (왼쪽 회전)
stu* rotateLeft(stu* parent) {
    stu* child = parent->rlink;
    stu* temp = child->llink;
    child->llink = parent;
    parent->rlink = temp;

    //부모 높이를 재계산
    //부모 기준으로 왼쪽 또는 오른쪽 자식노드가 있는 경우
    if (parent->llink != NULL || parent->rlink != NULL) {
        //부모 노드의 높이는 왼쪽 자식의 높이와 오른쪽 자식의 높이 중 큰 값에 1을 더하여 계산
        parent->nodeHeight = 1 + (getHeight(parent->llink) > getHeight(parent->rlink) ? 
            getHeight(parent->llink) : getHeight(parent->rlink) );
    }
    else {
        //부모 기준으로 왼쪽, 오른쪽 자식노드가 없으면 높이는 1이다.
        parent->nodeHeight = 1;
    }


    //회전 완료 후 자식 노드의 높이를 재계산
    //자식 기준으로 왼쪽 또는 오른쪽 자식노드가 있는 경우 마찬가지로 계산
    if (child->llink != NULL || child->rlink != NULL) {
        child->nodeHeight = 1 + (getHeight(child->llink) > getHeight(child->rlink) ? 
            getHeight(child->llink) : getHeight(child->rlink) );
    }
    else {
        child->nodeHeight = 1;
    }

    return child;
}

// LR 회전 (왼쪽 회전 후 오른쪽 회전)
stu* rotateLeftRight(stu* parent) {
    parent->llink = rotateLeft(parent->llink);
    return rotateRight(parent);
}

// RL 회전 (오른쪽 회전 후 왼쪽 회전)
stu* rotateRightLeft(stu* parent) {
    parent->rlink = rotateRight(parent->rlink);
    return rotateLeft(parent);
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

    if (balanceFactor > 1 && strcmp(data->id, root->llink->id) < 0) {
        return rotateRight(root);
    }

    if (balanceFactor < -1 && strcmp(data->id, root->rlink->id) > 0) {
        return rotateLeft(root);
    }

    if (balanceFactor > 1 && strcmp(data->id, root->llink->id) > 0) {
        return rotateLeftRight(root);
    }

    if (balanceFactor < -1 && strcmp(data->id, root->rlink->id) < 0) {
        return rotateRightLeft(root);
    }

    return root;
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

// 학생 정보 업데이트 기능
stu* updateNode(stu* root, const char* id) {
    stu* target = searchTree(root, id);
    if (target == NULL) {
        printf("업데이트할 학생 정보를 찾을 수 없습니다.\n");
        return root;
    }

    printf("학과를 입력하세요 : ");
    scanf("%s", target->dep);

    printf("이름을 입력하세요 : ");
    scanf("%s", target->name);

    printf("혈액형을 입력하세요 : ");
    scanf("%s", target->blood);

    printf("학년을 입력하세요 : ");
    scanf("%d", &target->grade);

    printf("키를 입력하세요 : ");
    scanf("%lf", &target->height);

    printf("몸무게를 입력하세요 : ");
    scanf("%lf", &target->weight);

    printf("학생 정보가 성공적으로 업데이트되었습니다.\n");
    return root;
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

    if (root->llink != NULL || root->rlink != NULL) {
        root->nodeHeight = 1 + (getHeight(root->llink) > getHeight(root->rlink) ? getHeight(root->llink) : getHeight(root->rlink));
    }
    else {
        root->nodeHeight = 1;
    }

    int balanceFactor = getBalanceFactor(root);

    // LL 불균형
    if (balanceFactor > 1 && getBalanceFactor(root->llink) >= 0) {
        return rotateRight(root);
    }

    // LR 불균형
    if (balanceFactor > 1 && getBalanceFactor(root->llink) < 0) {
        root->llink = rotateLeft(root->llink);
        return rotateRight(root);
    }

    // RR 불균형
    if (balanceFactor < -1 && getBalanceFactor(root->rlink) <= 0) {
        return rotateLeft(root);
    }

    // RL 불균형
    if (balanceFactor < -1 && getBalanceFactor(root->rlink) > 0) {
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


int menu() {
    int code;
    while (1) {
        printf("\n----------------------------------");
        printf("\n  학생 정보 관리 프로그램 AVL 트리 ");
        printf("\n----------------------------------");
        printf("\n 1. 학생 정보 입력 ");
        printf("\n 2. 학생 정보 출력(오름차순) ");
        printf("\n 3. 학생 정보 출력(내림차순) ");
        printf("\n 4. 검색할 학생 정보 ");
        printf("\n 5. 학생 정보 업데이트 ");
        printf("\n 6. 삭제할 학생 정보 ");
        printf("\n 7. 프로그램 종료 ");

        printf("\n---------------------------");
        printf("\n 메뉴를 입력 : ");

        if (scanf("%d", &code) == 1 && code >= 1 && code <= 7) {
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
            char updateId[10];
            printf("업데이트할 학생의 학번을 입력하세요: ");
            scanf("%s", updateId);
            root = updateNode(root, updateId);
        }
        else if (code == 6) {
            char deleteId[10];
            printf("삭제할 학생의 학번을 입력하세요: ");
            scanf("%s", deleteId);
            root = deleteNode(root, deleteId);
        }
        else if (code == 7) {
            break;
        }
    }

    free(data);
    return 0;
}
