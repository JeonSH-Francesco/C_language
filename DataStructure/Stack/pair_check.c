#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element; //스택 요소(element)의 자료형을 char 로 정의

typedef struct stackNode {
	element data;
	struct stackNode* link;
}stackNode;

stackNode* top; //스택의 top 노드를 지정하기 위해 포인터 top 선언

//스택이 공백 상태인지 확인하는 연산
int isEmpty() {
	if (top == NULL) { return 1; }
	else return 0;
}

void push(element item) {
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stackNode* temp = top;

	if (isEmpty()) {
		printf("\n\nStack is Empty!\n");
		return 0;
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}

}

int testPair(char* exp) {
	char symbol, open_pair;
	int i, length = strlen(exp);
	top = NULL;

	for (i = 0; i < length; i++) {
		symbol = exp[i];

		switch (symbol) {
			//왼쪽 괄호는 스택에 저장
		case'(':
		case'{':
		case'[':
			push(symbol); break;
			//오른쪽 괄호를 읽으면,
		case')':
		case'}':
		case']':
			if (top == NULL) {
				return 0;
			}
			else {
				//스택에서 마지막 읽은 괄호를 꺼냄
				open_pair = pop();
				//괄호 쌍이 맞는지 검사
				if ((open_pair == '(' && symbol != ')') ||
					(open_pair == '[' && symbol != ']') ||
					(open_pair == '{' && symbol != '}')) {
					return 0; //괄호 쌍이 틀리면 수식 오류
				}
				//괄호 쌍이 맞으면 다음 symbol 검사를 계속함.
				else break;
			}
		}
	}
	if (top == NULL) return 1; //수식 검사를 마친 후 스택이 공백이면 1 반환 -> 공백인 경우가 올바르게 괄호쌍이 이루어진 경우이다.
	else return 0; //공백이 아니면 0을 반환(수식 괄호 틀림)

}

void main(void) {
	char* express = "{(A+B)-3}*5+[{cos(x+y)+7}-1]*4";
	printf("%s",express);

	if (testPair(express) == 1) {
		printf("\n\n수식의 괄호가 알맞게 사용되었습니다.");
	}
	else {
		printf("\n\n수식의 괄호가 틀렸습니다.");
	}
}
