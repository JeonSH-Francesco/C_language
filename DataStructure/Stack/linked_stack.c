#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element; //스택 원소(element)의 자료형을 int로 정의

typedef struct stackNode { //스택의 노드를 구조체로 정의
	element data;
	struct StackNode* link;
}stackNode;

stackNode* top;    //스택의 top 노드를 지정하기 위해 포인터 top선언

//스택이 공백 상태인지 확인하는 연산
int isEmpty() {
	if (top == NULL) {
		return 1;
	}
	else return 0;
}

//스택의 top에 원소를 삽입하는 연산
void push(element item) {
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top; //삽입 노드를 top 위에 연결
	top = temp; //top 위치를 삽입 노드로 이동
	//(새로 삽입한 노드가 현재 스택의 마지막 노드 top이 가리키는 노드)
}

element pop() {
	element item;
	stackNode* temp = top; //temp를 top노드에 설정하여 삭제할 노드를 가리키게 한다.

	if (top == NULL) { //스택이 공백 리스트인 경우
		printf("\n\nStack is empty!\n");
		return 0;
	}
	else { //스택이 공백 리스트가 아닌 경우
		item = temp->data;
		top = temp->link; //top의 위치를 삭제 노드 아래로 이동
		free(temp); // 삭제된 노드의 메모리 반환
		return item; //삭제된 원소 반환
	}
}

element peek() {
	if (top == NULL) {
		printf("\n\nStack is Empty!\n");
		return 0;
	}
	else {
		return(top->data); //현재 top의 원소 반환
	}
}

void PrintStack() {
	stackNode* p = top;

	printf("\nStack [");
	while (p) {
		printf("%d ",p->data);
		p = p->link;
	}
	printf("] ");
}

void main(void) {
	element item;
	top = NULL;
	printf("\n**연결 스택 연산**\n");
	PrintStack();
	push(1); PrintStack();
	push(2); PrintStack();
	push(3); PrintStack();

	item = peek(); PrintStack();//현재 top원소 출력
	printf("peek=> %d",item);

	item = pop(); PrintStack();
	printf("\tpop => %d",item);

	item = pop(); PrintStack();
	printf("\tpop => %d", item);

	item = pop(); PrintStack();
	printf("\tpop => %d", item);
}

/*
**연결 스택 연산**

Stack []
Stack [1 ]
Stack [2 1 ]
Stack [3 2 1 ]
Stack [3 2 1 ] peek=> 3
Stack [2 1 ]    pop => 3
Stack [1 ]      pop => 2
Stack []        pop => 1
*/
