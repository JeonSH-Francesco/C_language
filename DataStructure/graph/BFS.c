#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_VERTEX 10 // 그래프의 최대 정점 개수
#define FALSE 0
#define TRUE 1

// 인접 리스트 노드를 나타내는 구조체
typedef struct graphNode {
    int vertex;
    struct graphNode* link;
} graphNode;

// 그래프를 나타내는 구조체
typedef struct graphType {
    int n;                        // 그래프의 정점 개수
    graphNode* adjList[MAX_VERTEX]; // 인접 리스트 배열
    int visited[MAX_VERTEX];      // 방문 여부 배열
} graphType;

// 큐 노드 구조체
typedef struct QNode {
    int data;
    struct QNode* link;
} QNode;

// 연결 큐 구조체
typedef struct {
    QNode* front, * rear;
} LQueueType;

// 연결 큐 생성
LQueueType* createLinkedQueue() {
    LQueueType* LQ = (LQueueType*)malloc(sizeof(LQueueType));
    LQ->front = NULL;
    LQ->rear = NULL;
    return LQ;
}

// 큐가 비었는지 확인
int isEmpty(LQueueType* LQ) {
    if (LQ->front == NULL) {
        printf("\nLinked Queue is empty!\n");
        return 1;
    }
    return 0;
}

// 큐에 데이터 삽입
void enQueue(LQueueType* LQ, int item) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->data = item;
    newNode->link = NULL;
    if (LQ->front == NULL) {
        LQ->front = newNode;
        LQ->rear = newNode;
    }
    else {
        LQ->rear->link = newNode;
        LQ->rear = newNode;
    }
}

// 큐에서 데이터 제거
int deQueue(LQueueType* LQ) {
    QNode* old = LQ->front;
    int item;
    if (isEmpty(LQ)) return 0;
    item = old->data;
    LQ->front = LQ->front->link;
    if (LQ->front == NULL) {
        LQ->rear = NULL;
    }
    free(old);
    return item;
}

// 그래프 초기화
void createGraph(graphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTEX; v++) {
        g->visited[v] = FALSE;
        g->adjList[v] = NULL;
    }
}

// 정점 삽입
void insertVertex(graphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTEX) {
        printf("그래프 정점 개수를 초과했습니다.\n");
        return;
    }
    g->n++;
}

// 간선 삽입
void insertEdge(graphType* g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        printf("그래프에 없는 정점입니다.\n");
        return;
    }
    graphNode* node = (graphNode*)malloc(sizeof(graphNode));
    node->vertex = v;
    node->link = g->adjList[u];
    g->adjList[u] = node;
}

// 인접 리스트 출력
void print_adjList(graphType* g) {
    for (int i = 0; i < g->n; i++) {
        graphNode* p = g->adjList[i];
        printf("\n정점 %c의 인접 리스트", i + 65);
        while (p) {
            printf(" -> %c", p->vertex + 65);
            p = p->link;
        }
    }
    printf("\n");
}

// BFS 탐색
void BFS_adjList(graphType* g, int v) {
    graphNode* w;
    LQueueType* Q = createLinkedQueue();
    g->visited[v] = TRUE;
    printf(" %c", v + 65);
    enQueue(Q, v);
    while (!isEmpty(Q)) {
        v = deQueue(Q);
        for (w = g->adjList[v]; w; w = w->link) {
            if (!g->visited[w->vertex]) {
                g->visited[w->vertex] = TRUE;
                printf(" %c", w->vertex + 65);
                enQueue(Q, w->vertex);
            }
        }
    }
}

// 메인 함수
int main() {
    graphType* G9 = (graphType*)malloc(sizeof(graphType));
    createGraph(G9);

    for (int i = 0; i < 7; i++) {
        insertVertex(G9, i);
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

    printf("\nG9의 인접 리스트");
    print_adjList(G9);

    printf("\n\nBFS >> ");
    BFS_adjList(G9, 0);

    return 0;
}
