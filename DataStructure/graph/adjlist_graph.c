#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30

//인접 리스트의 노드 구조를 구조체로 정의
typedef struct graphNode {
	int vertex; //정점을 나타내는 데이터 필드
	struct graphNode* link; //다음 인접 정점을 연결하는 링크 필드
}graphNode;

//그래프를 인접 리스트로 표현하기 위한 구조체 정의
typedef struct graphType {
	int n; //그래프 정점 개수
	graphNode* adjList[MAX_VERTEX]; //그래프 정점에 대한 헤드 포인터 배열
}graphType;

//공백 그래프를 생성하는 연산
void createGraph(graphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTEX; v++) {
		g->adjList[v] = NULL;
	}
}

//그래프 g에 정점 v를 삽입하는 연산
void insertVertex(graphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTEX) {
		printf("\n그래프 정점의 개수를 초과하였습니다.");
		return;
	}
	g->n++;
}


//그래프 g에 간선 (u,v)를 삽입하는 연산
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;

	//간선 (u,v)를 삽입하기 위해 정점 u와 정점 v가 현재 그래프에 있는지 확인
	if (u >= g->n || v >= g->n) {
		printf("\n그래프에 없는 정점입니다!");
		return;
	}
	node = (graphNode*)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = g->adjList[u]; //삽입 간선에 대한 노드를 리스트의 첫 번째 노드로 연결
	g->adjList[u] = node;
}

//그래프 g의 각 정점에 대한 인접 리스트를 출력하는 연산
void print_adjList(graphType* g) {
	int i;
	graphNode* p;
	for (i = 0; i < g->n; i++) {
		printf("\n\t\t정점 %c의 인접 리스트",i+65);
		p = g->adjList[i];
		while (p) {
			printf("-> %c",p->vertex+65);
			p = p->link;
		}
	}
}
void main() {
    int i;
    graphType* G1, * G2, * G3, * G4;
    G1 = (graphType*)malloc(sizeof(graphType));
    G2 = (graphType*)malloc(sizeof(graphType));
    G3 = (graphType*)malloc(sizeof(graphType));
    G4 = (graphType*)malloc(sizeof(graphType));

    createGraph(G1);
    createGraph(G2);
    createGraph(G3);
    createGraph(G4);

    // 그래프 G1
    for (i = 0; i < 4; i++) {
        insertVertex(G1, i); // G1의 정점 0~3 삽입 
    }
    insertEdge(G1, 0, 3);
    insertEdge(G1, 0, 1);
    insertEdge(G1, 1, 3);
    insertEdge(G1, 1, 2);
    insertEdge(G1, 1, 0);
    insertEdge(G1, 2, 3);
    insertEdge(G1, 2, 1);
    insertEdge(G1, 3, 2);
    insertEdge(G1, 3, 1);
    insertEdge(G1, 3, 0);

    printf("\nG1의 인접 리스트");
    print_adjList(G1);

    // 그래프 G2
    for (i = 0; i < 3; i++) {
        insertVertex(G2, i); // G2의 정점 0~2 삽입
    }
    insertEdge(G2, 0, 2);
    insertEdge(G2, 0, 1);
    insertEdge(G2, 1, 2);
    insertEdge(G2, 1, 0);
    insertEdge(G2, 2, 1);
    insertEdge(G2, 2, 0);

    printf("\n\nG2의 인접 리스트");
    print_adjList(G2);

    // 그래프 G3
    for (i = 0; i < 4; i++) {
        insertVertex(G3, i); // G3의 정점 0~3 삽입
    }
    insertEdge(G3, 0, 3);
    insertEdge(G3, 0, 1);
    insertEdge(G3, 1, 3);
    insertEdge(G3, 1, 2);
    insertEdge(G3, 2, 3);

    printf("\n\nG3의 인접 리스트");
    print_adjList(G3);

    // 그래프 G4
    for (i = 0; i < 3; i++) {
        insertVertex(G4, i); // G4의 정점 0~2 삽입
    }
    insertEdge(G4, 0, 2);
    insertEdge(G4, 0, 1);
    insertEdge(G4, 1, 2);
    insertEdge(G4, 1, 0);

    printf("\n\nG4의 인접 리스트");
    print_adjList(G4);

    // 메모리 해제
    free(G1);
    free(G2);
    free(G3);
    free(G4);

    printf("\n\n");
}
