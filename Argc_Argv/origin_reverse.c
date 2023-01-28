#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int i,j;
	int tmp;
	int array[100];

	if(argc>5 && argc<=11){
	printf("origin: ");
	for(i=1;i<argc;i++){
	array[i]=atoi(argv[i]);	
	printf("%d ",array[i]);
	}

	printf("\nreverse: ");
	j=argc-1;
	for(i=1;i<(argc/2)+1;i++){
	tmp=array[i];
	array[i]=array[j];
	array[j]=tmp;
	j--;
	}
	for(i=1;i<argc;i++){
	 printf("%d ",array[i]);
	}
	printf("\n");

	}

	else
		printf("The number of the parameter is only 5 to 10!");

	return 0;
}
