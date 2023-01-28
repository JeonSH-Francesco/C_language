#include <stdio.h>
#include <stdlib.h>  //maclloc(),free()

int main(int argc,char *argv[]){
	int i,j;
	int tmp;
	int *ptr;

	if(argc>5 && argc<=11){
	ptr=(int*)malloc(sizeof(int)*argc);
	printf("origin: ");
	for(i=1;i<argc;i++){
	*(ptr+i)=atoi(argv[i]);
	printf("%d ",*(ptr+i));
	}
	printf("\nreverse: ");
	j=argc-1;
	for(i=1;i<(argc/2)+1;i++){
	tmp=*(ptr+i);
	*(ptr+i)=*(ptr+j);
	*(ptr+j)=tmp;
	j--;
	}
	for(i=1;i<argc;i++){
	printf("%d ",*(ptr+i));
	}
	printf("\n");
	free((int*)ptr);
	}

	else
		printf("The number of the parameter is only 5 to 10!");
	return 0;
}
