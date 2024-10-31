#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 5

typedef char element;

element queue[QUEUE_SIZE];
int front = -1; // front 전역 변수 초기화
int rear = -1;  // rear 전역 변수 초기화



// 큐가 비어있는지 확인하는 연산
int isEmpty() {
    if (front == -1) {
        return 1; // 큐가 비어있음
    }
    return 0;
}

// 큐가 가득 찬 상태인지 확인하는 연산
int isFull() {
    if ((rear + 1) % QUEUE_SIZE == front) {
        return 1; // 큐가 가득 참
    }
    return 0;
}

// 큐의 원소를 출력하는 연산
void PrintQueue() {
    int i = front;
    printf("\nQUEUE [");
    if (isEmpty()) {
        printf("Empty");
    }
    else {
        while (i != rear) {
            printf("%c ", queue[i]);
            i = (i + 1) % QUEUE_SIZE;
        }
        printf("%c ", queue[rear]); // rear 원소 출력
    }
    printf("]");
}

// 큐에 item 하나를 추가
void enqueue(element item) {
    if (isFull()) {
        printf("\n\nQueue is Full!\n");
        return;
    }
    if (isEmpty()) {
        front = 0; // 처음 enqueue 할 때 front 초기화
    }
    rear = (rear + 1) % QUEUE_SIZE; // rear 업데이트
    queue[rear] = item; // 큐에 원소 삽입
    printf("\nenqueue -> %c", item);
    PrintQueue();
}

// 큐에서 가장 앞에 있는 항목 제거
element dequeue() {
    if (isEmpty()) {
        printf("\n\nQueue is Empty!\n");
        return 0;
    }
    element item = queue[front]; // 제거할 원소 저장
    if (front == rear) { // 마지막 원소 제거 후 큐가 비게 될 경우
        front = rear = -1;
    }
    else {
        front = (front + 1) % QUEUE_SIZE; // front 업데이트
    }
    printf("\ndequeue -> %c", item);
    PrintQueue();
    return item;
}

// 큐의 가장 앞에 있는 항목 반환
element peek() {
    if (isEmpty()) {
        printf("\n\nQueue is Empty!\n");
        exit(1);
    }
    return queue[front]; // 현재 front의 원소 확인
}


void main(void) {
    element item;
    printf("순차 큐 연산\n");

    enqueue('A'); // 문자 A를 큐에 추가
    enqueue('B'); // 문자 B를 큐에 추가
    enqueue('C'); // 문자 C를 큐에 추가
    enqueue('D'); // 문자 D를 큐에 추가
    enqueue('E'); // 문자 E를 큐에 추가

    enqueue('F'); // 큐가 가득 찼으므로 출력

    item = peek();
    printf("\npeek -> %c\n", item);

    dequeue(); // 첫 번째 원소 제거
    dequeue(); // 두 번째 원소 제거
    dequeue(); // 세 번째 원소 제거
    dequeue(); // 네 번째 원소 제거

    dequeue(); // 마지막 원소 제거
    dequeue(); // 큐가 비어있으므로 출력
}
/*
result : 
순차 큐 연산

enqueue -> A
QUEUE [A ]
enqueue -> B
QUEUE [A B ]
enqueue -> C
QUEUE [A B C ]
enqueue -> D
QUEUE [A B C D ]
enqueue -> E
QUEUE [A B C D E ]

Queue is Full!

peek -> A

dequeue -> A
QUEUE [B C D E ]
dequeue -> B
QUEUE [C D E ]
dequeue -> C
QUEUE [D E ]
dequeue -> D
QUEUE [E ]
dequeue -> E
QUEUE [Empty]

Queue is Empty!

*/
