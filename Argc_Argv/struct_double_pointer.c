#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 20
#define MAX_NAME_LEN 40
#define MAX_BIRTH_LEN 20

/*
이중 포인터 사용 이유:
단일 포인터 사용시(자리바꿈,삽입,삭제 시)메모리 크기만큼 복제가 일어나는데,
size가 큰 경우, 메모리의 I/O 때문에 시스템의 성능을 떨어뜨리는데,
이중포인터의 경우, 주소의 4byte만 몇 번 이동하여 접근할 수 있다.
연산처리 속도가 커지고 시스템의 성능이 좋아진다.
*/


typedef unsigned char uint8_t;

typedef struct student_info{
	char stu_id[MAX_ID_LEN];
	uint8_t dept_id;
	char dept_name[MAX_NAME_LEN];
	uint8_t grade;
	char stu_name[MAX_NAME_LEN];
	char birthday[MAX_BIRTH_LEN];
}student_info;


int main(int argc,char *argv[]){
	FILE *ifp;
	char line[256];
	int line_num=0;
	int stu_cnt;
	student_info **sts;
	student_info tmp;
	int i;
	int range;

	ifp=fopen("students_10.txt","r");

	while(!feof(ifp)){
	fgets(line,256,ifp);
	line_num++;
	}

	stu_cnt= line_num-2;
	printf("Total students: %d\n",line_num-2);

	sts=(student_info**)malloc(sizeof(student_info*)*stu_cnt);
	for(int i=0;i<=stu_cnt;i++){
        sts[i]=(student_info*)malloc(sizeof(student_info));
	}

	fseek(ifp,0,SEEK_SET);
	line_num =-1;

	while(!feof(ifp)){
	line_num++;

	if(line_num==0){
		fgets(line,256,ifp);
		continue;
	}
	else {
		fscanf(ifp,"%s %d %s %d %s %s",tmp.stu_id,&tmp.dept_id,tmp.dept_name,&tmp.grade,tmp.stu_name,tmp.birthday);
		memcpy(sts[line_num-1],&tmp,sizeof(tmp));
		bzero(&tmp,sizeof(tmp));
		}
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Idx\tStudent ID\tDepartment ID\tDepartment Name\t\tStudent Name\t\tGrade\tBirthday\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");

	for(i=0;i<stu_cnt;i++){
		printf("%d\t%s\t%d\t\t%15s\t%15s\t\t\t%d\t%s\n",i+1,sts[i]->stu_id,sts[i]->dept_id,sts[i]->dept_name,sts[i]->stu_name,sts[i]->grade,sts[i]->birthday);
	}

	for(int i=0;i<stu_cnt;i++){
        free(sts[i]);
	}
	free((student_info**)sts);
	fclose(ifp);
	return 0;

}


