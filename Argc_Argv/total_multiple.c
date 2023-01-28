#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int i,stotal=0,mtotal=1;
	int *ptr;
	int array[100];
	ptr=array;

	for(i=1;i<argc;i++){
	array[i]=atoi(argv[i]);
	if(i!=argc-1)
		printf("%d+",array[i]);
	else
		printf("%d",array[i]);
	stotal=stotal+array[i];
	}
	printf("=%d",stotal);
	printf("\n");

	for(i=1;i<argc;i++){
	if(i!=argc-1)
		printf("%dx",array[i]);
	else
		printf("%d",array[i]);
	mtotal=mtotal*array[i];
	}
	printf("=%d",mtotal);
	printf("\n");
	return 0;
}
