#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 5

typedef int element; //스택 원소의 자료형을 int로 정의
element stack[STACK_SIZE]; //1차원 배열 스택 선언
int top = -1; //top 전역 변수로 초기화

//스택이 공백 상태인지 확인하는 연산
//스택이 비어있을 때 true를 반환
int isEmpty() {
	if (top == -1) { return 1; }
	else return 0;
}

//스택이 가득 찬 상태인지 확인하는 연산
//스택이 가득 찼다면 true를 반환
int isFull() {
	if (top == STACK_SIZE) { return 1; }
	else return 0;
}

//스택에 item 하나를 가장 윗 부분에 추가
void push(element item) {
	if (isFull()) {
		printf("\n\nStack is Full!\n");
		return;
	}

	else stack[++top] = item; //top을 증가시킨 후 현재 top에 원소 삽입

	if (top >= 0) {
		printf("\npush -> %d", item);
	}
}

//스택에서 가장 위에 있는 항목 제거
element pop() {
	if (isEmpty()) {
		printf("\n\nStack is Empty!");
		return 0;
	}
	else return stack[top--]; //현재 top 의 원소를 삭제한 후 top 감소
}

//스택의 가장 위에 있는 항목 stack 배열 반환
element peek() {
	if (isEmpty()) {
		printf("\n\nStack is Empty!\n");
		exit(1);
	}
	else return stack[top]; //현재 top의 원소 확인
}

//스택의 원소를 출력하는 연산
void PrintStack() {
	int i;
	printf("\n");
	printf("STACK [");
	for (i = 0; i <= top; i++) {
		printf("%d ",stack[i]);
	}
	printf("]");
}

void main(void) {
	element item;
	printf("순차 스택 연산\n");
	push(0); PrintStack();
	push(1); PrintStack();
	push(2); PrintStack();
	push(3); PrintStack();
	push(4); PrintStack();

	push(5); PrintStack();

	push(10); 

	item = peek(); PrintStack();
	printf("\npeek-> %d\n",item);

	item = pop(); PrintStack();
	printf("\npop -> %d",item);

	item = pop(); PrintStack();
	printf("\npop -> %d",item);

	item = pop(); PrintStack();
	printf("\npop -> %d", item);

	item = pop(); PrintStack();
	printf("\npop -> %d", item);

	item = pop(); PrintStack();
	printf("\npop -> %d", item);

	item = pop(); PrintStack();
	printf("\npop -> %d", item);

	item = pop();
}
/*
result : 

순차 스택 연산

push -> 0
STACK [0 ]
push -> 1
STACK [0 1 ]
push -> 2
STACK [0 1 2 ]
push -> 3
STACK [0 1 2 3 ]
push -> 4
STACK [0 1 2 3 4 ]
push -> 5
STACK [0 1 2 3 4 5 ]

Stack is Full!

STACK [0 1 2 3 4 5 ]
peek-> 5

STACK [0 1 2 3 4 ]
pop -> 5
STACK [0 1 2 3 ]
pop -> 4
STACK [0 1 2 ]
pop -> 3
STACK [0 1 ]
pop -> 2
STACK [0 ]
pop -> 1
STACK []
pop -> 0

Stack is Empty!
*/
