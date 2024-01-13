#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MyStruct
{
	struct students* llink;
	struct students* rlink;

	char id[20];    //학번
	char dep[20];	//학과
	char name[20];	//이름
	char blood[5];	//혈액형
	int grade;       //학년
	float height;   //키
	float weight;   //몸무게

}students;

students* insertNode(students* root, students* data)
{
	students* temp;
	students* newNode;
	temp = root;

	if (root == NULL)
	{
		newNode = (students*)malloc(sizeof(students));

		newNode->llink = NULL;
		newNode->rlink = NULL;

		strcpy(newNode->id, data->id);
		strcpy(newNode->name, data->name);

		root = newNode;
		temp = newNode;
	}


	else if (strcmp(root->id, data->id) > 0)
	{
		temp->llink = insertNode(temp->llink, data);
	}

	else if (strcmp(root->id, data->id) < 0)
	{
		temp->rlink = insertNode(temp->rlink, data);
	}

	else
	{
		printf("같은 값 입력은 불가능합니다.");
		return;
	}

	return temp;
}

void printTree_1(students* root) //오름차순
{
	if (root != NULL)
	{
		printTree_1(root->llink);
		printf("\n %s, %s", root->id, root->name);
		printTree_1(root->rlink);
	}
}

void printTree_2(students* root) //내림차순
{
	if (root != NULL)
	{
		printTree_2(root->rlink);
		printf("\n %s, %s", root->id, root->name);
		printTree_2(root->llink);
	}
}

int searchTree(students* root, students* data)
{
	students* temp;
	temp = root;

	if (root == NULL)
	{
		return 0;
	}

	else if (strcmp(root->id, data->id) > 0)
		searchTree(temp->llink, data);

	else if (strcmp(root->id, data->id) < 0)
		searchTree(temp->rlink, data);

	else
	{
		printf("\n%s %s 학생을 찾았습니다~!!", temp->id, temp->name);
		return 1;
	}
	return 0;
}

students* deleteNode(students* root, students* data, students* parent) {
	students* temp = root;

	if (root == NULL)
	{
		printf("삭제할 학생이 없습니다.\n");
		return NULL;
	}
	else if (strcmp(temp->id, data->id) > 0)
		deleteNode(temp->llink, data, temp);
	else if (strcmp(temp->id, data->id) < 0)
		deleteNode(temp->rlink, data, temp);

	else
	{
		printf("%s %s 학생을 삭제합니다.\n", temp->id, temp->name);

		if (temp->llink == NULL && temp->rlink == NULL) {
			//root를 삭제할 경우
			if (parent == NULL) {
				root = NULL;
			}
			else if (parent->rlink == temp) {
				parent->rlink = NULL;
			}
			else {
				parent->llink = NULL;
			}

		}


		//자식노드가 2개인 경우 :
		else if (temp->llink != NULL && temp->rlink != NULL) {
			temp->llink = temp;

		}


		//자식노드가 1개인 경우 : 해당 노드의 자식을 해당 노드의 위치로 이동
		else {
			//root 노드를 삭제할 경우
			if (parent == NULL) {
				if (temp->llink != NULL) root = temp->llink;
				else root = temp->rlink;
			}
			//자식의 위치를 찾아서 부모 노드와 연결
			else if (parent->rlink == temp) {
				if (temp->rlink != NULL) parent->rlink = temp->rlink;
				else parent->rlink = temp->llink;
			}
			else {
				if (temp->rlink != NULL) parent->llink = temp->rlink;
				else parent->llink = temp->llink;
			}
		}
		free(temp);
	}
	return root;
}
/*//자식노드가 2개인 경우 :
		else if (temp->llink != NULL && temp->rlink != NULL) {

			child= temp->rlink;

			//오른쪽 서브트리에서 제일 작은 값으로 이동
			while (child->llink != NULL) {
				prev = child;
				child = child->llink;
			}
			//제일 작은 값은 부모노드와 단절
			if (prev->llink == child) {
				if (child->rlink != NULL)
					prev->llink =child->rlink;
				else
					prev->llink = NULL;
			}
			else
				prev->rlink = NULL;


			//삭제노드의 양쪽을 제일 작은값의 노드에 링크
			child->llink = temp->llink;
			child->rlink = temp->rlink;

			//삭제노드의 부모노드와 링크
			if (parent == NULL)
				root = child;
			else if (parent->llink == temp)
				parent->llink = child;
			else
				parent->rlink = child;

		}*/

int menu() {
	int code;
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
	scanf("%d", &code);
	return code;
}

void main()
{
	int code = 0, result = 0;
	students* root = NULL;  //트리의 시작 주소를 저장하는 변수
	students* data = NULL;  //학생정보 저장 변수
	data = (students*)malloc(sizeof(students));


	while (1)
	{
		code = menu();
		if (code == 1)
		{
			printf("학번을 입력하세요 : ");
			scanf("%s", data->id);

			printf("이름을 입력하세요 : ");
			scanf("%s", data->name);
			root = insertNode(root, data);
		}
		if (code == 2)
		{
			printf("삭제할 학생의 학번을 입력하세요 : ");
			scanf("%s", data->id);
			root = deleteNode(root, data, NULL);
		}
		if (code == 3)
		{
			printf("찾을 학생 학번을 입력하세요 : ");
			scanf("%s", data->id);
			result = searchTree(root, data);
		}
		if (code == 4) printTree_1(root);
		if (code == 5) printTree_2(root);

		if (code == 6) break;
	}
}
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct MyStruct
{
	struct students* llink;
	struct students* rlink;

	char id[20];    //학번
	char dep[20];	//학과
	char name[20];	//이름
	char blood[5];	//혈액형
	int grade;       //학년
	float height;   //키
	float weight;   //몸무게

}students;

students* insertNode(students* root, students* data)
{
	students* temp;
	students* newNode;
	temp = root;

	if (root == NULL)
	{
		newNode = (students*)malloc(sizeof(students));

		newNode->llink = NULL;
		newNode->rlink = NULL;

		strcpy(newNode->id, data->id);
		strcpy(newNode->dep, data->dep);

		root = newNode;
		temp = newNode;
	}


	else if (strcmp(root->id, data->id) > 0)
	{
		temp->llink = insertNode(temp->llink, data);
	}

	else if (strcmp(root->id, data->id) < 0)
	{
		temp->rlink = insertNode(temp->rlink, data);
	}

	else
	{
		printf("같은 값 입력은 불가능합니다.");
		return temp;
	}

	return temp;
}

void printTree_1(students* root) //오름차순
{
	if (root != NULL)
	{
		printTree_1(root->llink);
		printf("\n %s, %s", root->id, root->name);
		printTree_1(root->rlink);
	}
}

void printTree_2(students* root) //내림차순
{
	if (root != NULL)
	{
		printTree_2(root->rlink);
		printf("\n %s, %s", root->id, root->name);
		printTree_2(root->llink);
	}
}

int searchTree(students* root, students* data)
{
	students* temp;
	temp = root;

	if (root == NULL)
	{
		return 0;
	}

	else if (strcmp(root->id, data->id) > 0)
		searchTree(temp->llink, data);

	else if (strcmp(root->id, data->id) < 0)
		searchTree(temp->rlink, data);

	else
		printf("\n%s %s 학생을 찾았습니다~!!", temp->id, temp->name);

	return 1;


}

students* deleteNode(students* root, students* data) {
	students* temp, * pre, * parent;
	pre = temp = root;

	if (root == NULL) {
		printf("정보가 없습니다.\n");
	}
	else if (strcmp(root->id, data->id) > 0)//내림차순
		temp->llink = deleteNode(temp->llink, data);

	else if (strcmp(root->id, data->id) < 0)//오름차순
		temp->rlink = deleteNode(temp->rlink, data);

	else {

		//지울 학생의 주소 temp

		//자식 노드가 하나도 없는 경우
		if (temp->llink == NULL && temp->rlink == NULL) {
			return NULL;
		}

		else if (temp->llink != NULL && temp->rlink != NULL) {
			//자식 노드가 2개 인경우
			parent = temp;
			pre = temp->llink;

			while (pre->rlink != NULL) {
				parent = pre;
				pre = pre->rlink;
			}
			if (parent->llink == pre)

				parent->llink = pre->llink;

			else//parent->rlink==pre인 경우
				parent->rlink = pre->llink;

			strcpy(temp->id, pre->id);

			return temp;

		}

		else {
			// 자식 노드가 하나인 경우
			//if(temp->llink !=NULL || temp->rlink !=NULL){

			if (temp->llink != NULL)
			{
				return temp->llink;
			}
			else
			{
				return temp->rlink;
			}


		}
		return temp;

	}

	return root;

}



int menu() {
	int code;
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
	scanf("%d", &code);
	return code;
}

void main()
{
	int code = 0, result = 0;
	students* root = NULL;  //트리의 시작 주소를 저장하는 변수
	students* data = NULL;  //학생정보 저장 변수

	data = (students*)malloc(sizeof(students));


	while (1)
	{
		code = menu();
		if (code == 1)
		{
			printf("학번을 입력하세요 : ");
			scanf("%s", data->id);

			//printf("학과를 입력하세요 : ");
			//scanf("%s",data->dep);

			printf("이름을 입력하세요 : ");
			scanf("%s", data->name);

			//printf("혈액형을 입력하세요 : ");
			//scanf("%s",data->blood);

			//printf("학년을 입력하세요 : ");
			//scanf("%d",&data->grade);

			//printf("키를 입력하세요 : ");
			//scanf("%f",&data->height);

			//printf("몸무게를 입력하세요 : ");
			//scanf("%f",&data->weight);

			root = insertNode(root, data);
		}
		if (code == 2)
		{
			printf("삭제할 학생의 학번을 입력하세요 : ");
			scanf("%s", data->id);
			root = deleteNode(root, data);
		}
		if (code == 3)
		{
			printf("찾을 학생 학번을 입력하세요 : ");
			scanf("%s", data->id);
			result = searchTree(root, data);
		}
		if (code == 4) printTree_1(root);
		if (code == 5) printTree_2(root);

		if (code == 6) break;
	}
}
*/
