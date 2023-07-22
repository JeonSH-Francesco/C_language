#include <stdio.h>

int main(){
  int num=0;
  int start=0;
  

  printf("Input even number: ");
  scanf("%d",&num);
  
  int end=num;
  for(int i=0;i<num-1;i++){
        if(i<num/2){
            start=i;
            end--;
        }   
        else{
            start--;
            end++;
        }
    
        for(int j=start;j>0;j--){
            printf(" ");
        }
        for(int j=start;j<end;j++){
            printf("*");
        }
        printf("\n");
    }

}
