#include <stdio.h>

int main(){
  int num=0;
  printf("Input number: ");
  scanf("%d",&num);
  
  for(int i=0;i<num;i++){
    for(int j=num-1;j>i;j--){
        printf(" ");
    }
	    
    for(int j=0;j<2*i+1;j++){
	    printf("*");
    }
    printf("\n");
  }
}
