#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 20
#define MAX_NAME_LEN 40
#define MAX_BIRTH_LEN 20

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
	student_info *students;
	int i;
	int range;
	unsigned int tmp;

	ifp=fopen("students_10.txt","r");

	while(!feof(ifp)){
	fgets(line,256,ifp);
	line_num++;
	}

	stu_cnt= line_num-2;
	printf("Total students: %d\n",line_num-2);

	students=(student_info*)malloc(sizeof(student_info)*stu_cnt);
	memset(students,0x0,sizeof(students));

	fseek(ifp,0,SEEK_SET);
	line_num =-1;

	while(!feof(ifp)){
	line_num++;

	if(line_num==0){
		fgets(line,256,ifp);
		continue;
	}
	else {
		fscanf(ifp,"%s",(char*)&students[line_num-1].stu_id);
		fscanf(ifp,"%d",&students[line_num-1].dept_id);
		fscanf(ifp,"%s",&students[line_num-1].dept_name);
		fscanf(ifp,"%d",&students[line_num-1].grade);
		fscanf(ifp,"%s",&students[line_num-1].stu_name);
		fscanf(ifp,"%s",&students[line_num-1].birthday);
		}
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Idx\tStudent ID\tDepartment ID\tDepartment Name\t\tStudent Name\t\tGrade\tBirthday\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");

	for(i=0;i<stu_cnt;i++){
		printf("%d\t%s\t%d\t\t%15s\t%15s\t\t\t%d\t%s\n",i+1,students[i].stu_id ,students[i].dept_id ,students[i].dept_name ,students[i].stu_name, students[i].grade ,students[i].birthday);
	}

	free((void*)students);
	fclose(ifp);
	return 0;

}


