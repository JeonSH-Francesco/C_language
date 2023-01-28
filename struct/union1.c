#include <stdio.h>

struct inform{
	int codenum;
	char student_name[20];
	char phone_num[11];
	int major;
	int grade;
		union Spec{
			int num;//university student number
			unsigned long long snum;//graduate school stduent number
	}spec;
};


int main(){
    int i;
    struct inform p[5]={};
    union Spec spec;

   for(i=0;i<5;i++){
   printf("### student %d info ###",i+1);
   printf("\n--> input code: ");
   scanf("%d",&p[i].codenum);
   printf("--> input sutdent id: ");
   scanf("%d",&p[i].spec.snum);
   printf("--> input student name: ");
   scanf("%s",p[i].student_name);
   printf("--> input phone number: ");
   scanf("%s",p[i].phone_num);
   printf("--> input major: ");
   scanf("%d",&p[i].major);
   printf("--> input grade: ");
   scanf("%d",&p[i].grade);

   if((p[i].codenum)>2 || (p[i].grade>4))
   {printf("You entered the wrong!! Please check this student's information.\n");
   --i;
   continue;
   }

   }

   printf("\nCode\tStudent ID\t Name\t Phone\t\t  Major\t\t Grade\n");
   printf("==========================================================================");
   for(i=0;i<5;i++){
   printf("\n%d\t%d\t %s\t %s\t %d\t\t %d",p[i].codenum, p[i].spec.snum, p[i].student_name, p[i].phone_num, p[i].major, p[i].grade);
   printf("\n");

   }

   return 0;
}
