#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAX_VERTEX 10 // 그래프의 최대 정점 개수
#define FALSE 0       // 방문 여부를 나타내는 상수
#define TRUE 1

// 그래프의 인접 리스트 노드를 나타내는 구조체
typedef struct graphNode {
    int vertex;               // 정점 번호
    struct graphNode* link;   // 다음 인접 노드
} graphNode;

// 그래프를 나타내는 구조체
typedef struct graphType {
    int n;                    // 그래프의 정점 개수
    graphNode* adjList[MAX_VERTEX]; // 인접 리스트의 헤드 노드 배열
    int visited[MAX_VERTEX];  // 정점의 방문 여부를 기록하는 배열
} graphType;

// 스택 노드를 나타내는 구조체
typedef struct stackNode {
    int data;                 // 스택에 저장된 데이터
    struct stackNode* link;   // 다음 스택 노드
} stackNode;

stackNode* top; // 스택의 최상단을 가리키는 포인터

// 스택이 비어 있는지 확인
int isEmpty() {
    if (top == NULL) {
        return 1; // 스택이 비어 있으면 1 반환
    }
    else {
        return 0; // 스택이 비어 있지 않으면 0 반환
    }
}

// 스택에 데이터를 push
void push(int item) {
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode)); // 새로운 노드 생성
    temp->data = item;       // 데이터 저장
    temp->link = top;        // 현재 스택의 top을 새 노드의 link로 연결
    top = temp;              // 새 노드를 top으로 설정
}

// 스택에서 데이터를 pop
int pop() {
    int item;
    stackNode* temp = top;

    if (isEmpty()) { // 스택이 비어 있으면
        printf("\n\n Stack is Empty !\n");
        return 0;    // 0 반환
    }
    else {
        item = temp->data; // 최상단 데이터 가져오기
        top = temp->link;  // top을 다음 노드로 변경
        free(temp);        // 기존 top 노드 메모리 해제
        return item;       // 데이터를 반환
    }
}

// 그래프 초기화
void createGraph(graphType* g) {
    int v;
    g->n = 0; // 정점 개수를 0으로 초기화
    for (v = 0; v < MAX_VERTEX; v++) {
        g->visited[v] = FALSE; // 모든 정점을 방문하지 않은 상태로 초기화
        g->adjList[v] = NULL;  // 인접 리스트를 NULL로 초기화
    }
}

// 그래프에 정점 추가
void insertVertex(graphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTEX) { // 최대 정점 개수를 초과하면
        printf("\n 그래프 정점의 개수를 초과하였습니다.\n");
        return;
    }
    g->n++; // 정점 개수 증가
}

// 그래프에 간선 추가
void insertEdge(graphType* g, int u, int v) {
    graphNode* node;
    if (u >= g->n || v >= g->n) { // 정점이 그래프에 없는 경우
        printf("\n 그래프에 없는 정점입니다.");
        return;
    }
    node = (graphNode*)malloc(sizeof(graphNode)); // 새로운 간선 노드 생성
    node->vertex = v; // 연결된 정점 번호 저장
    node->link = g->adjList[u]; // 기존 인접 리스트의 첫 노드에 연결
    g->adjList[u] = node; // 새로운 노드를 인접 리스트의 첫 노드로 설정
}

// 그래프의 인접 리스트를 출력
void print_adjList(graphType* g) {
    int i;
    graphNode* p;
    for (i = 0; i < g->n; i++) {
        printf("\n\t\t정점 %c의 인접 리스트", i + 65); // 정점 번호를 문자로 출력
        p = g->adjList[i]; // 각 정점의 인접 리스트 순회
        while (p) {
            printf("-> %c", p->vertex + 65); // 연결된 정점 출력
            p = p->link; // 다음 인접 노드로 이동
        }
    }
}

// DFS(깊이 우선 탐색) 함수
void DFS_adjList(graphType* g, int v) {
    graphNode* w; // 인접 정점을 탐색하기 위한 포인터
    top = NULL; // 스택 초기화
    push(v); // 시작 정점을 스택에 push
    g->visited[v] = TRUE; // 시작 정점을 방문 처리
    printf(" %c", v + 65); // 방문한 정점을 출력

    // 스택이 공백이 아닌 동안 반복
    while (!isEmpty()) {
        v = top->data; // 스택의 최상단 정점을 확인 (pop하지 않음)
        w = g->adjList[v]; // 현재 정점의 인접 리스트를 탐색

        // 인접 정점을 찾는 동안 반복
        while (w) {
            if (!g->visited[w->vertex]) { // 방문하지 않은 인접 정점이 있으면
                push(w->vertex); // 스택에 push
                g->visited[w->vertex] = TRUE; // 방문 처리
                printf(" %c", w->vertex + 65); // 방문한 정점 출력
                v = w->vertex; // 현재 정점을 갱신
                w = g->adjList[v]; // 새로운 정점의 인접 리스트로 이동
            }
            else {
                w = w->link; // 다음 인접 정점으로 이동
            }
        }
        pop(); // 더 이상 방문할 인접 정점이 없으면 스택에서 pop
    }
}

void main() {
    int i;
    graphType* G9; // 그래프 선언
    G9 = (graphType*)malloc(sizeof(graphType)); // 그래프 메모리 할당
    createGraph(G9); // 그래프 초기화

    // 그래프 G9 구성
    for (i = 0; i < 7; i++) {
        insertVertex(G9, i); // 7개의 정점 추가
    }
    insertEdge(G9, 0, 2);
    insertEdge(G9, 0, 1);
    insertEdge(G9, 1, 4);
    insertEdge(G9, 1, 3);
    insertEdge(G9, 1, 0);
    insertEdge(G9, 2, 4);
    insertEdge(G9, 2, 0);
    insertEdge(G9, 3, 6);
    insertEdge(G9, 3, 1);
    insertEdge(G9, 4, 6);
    insertEdge(G9, 4, 2);
    insertEdge(G9, 4, 1);
    insertEdge(G9, 5, 6);
    insertEdge(G9, 6, 5);
    insertEdge(G9, 6, 4);
    insertEdge(G9, 6, 3);

    printf("\n G9의 인접 리스트 ");
    print_adjList(G9); // 인접 리스트 출력

    printf("\n\nDFS>>");
    DFS_adjList(G9, 0); // DFS 탐색 시작
}
/*

 G9의 인접 리스트
                정점 A의 인접 리스트-> B-> C
                정점 B의 인접 리스트-> A-> D-> E
                정점 C의 인접 리스트-> A-> E
                정점 D의 인접 리스트-> B-> G
                정점 E의 인접 리스트-> B-> C-> G
                정점 F의 인접 리스트-> G
                정점 G의 인접 리스트-> D-> E-> F

DFS>> A B D G E C F
*/
