#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN 1024

int main(int argc, char* argv[]){

   if( argc < 2 || argc > 2 ){
      printf("Usage : %s [URL]\n", argv[0]);
      return -1;
   }

   printf("========== Download %s source ==========\n", argv[1]);

   char commend[50] = "wget -O index.html ";
   strcat(commend, argv[1]);

   system(commend);

   FILE* fp = fopen("index.html", "r");
   char* pos;
   char* pos_end;
   char buf[MAX_BUF_LEN] = "";
   char result[MAX_BUF_LEN] = "";
   int cnt = 0;

   FILE* fp_result = fopen("url_list.txt", "w+");

   //repeat untill meet EOF
   while(!feof(fp)){

      fgets(buf, MAX_BUF_LEN, fp);
      //printf("buf : %s\n", buf);

      //if find start point ("http)
      if((pos = strstr(buf, "\"http")) != NULL){

         cnt++;
         //printf("cnt : %d\r", cnt);

         //find end point "
         pos_end = strchr(pos+1, '\"');
         strncpy(result, pos+1, pos_end-pos-1);
         //printf("pos : %p\n", pos);
         //printf("pos_end : %p\n", pos_end);

         //re setting SEEK_CUR -> pos_end + 1
         fseek(fp, -strlen(buf)+(pos_end-buf)+1, SEEK_CUR);

         strcat(result, "\n");
         fwrite(result, 1, strlen(result), fp_result);

         //printf("bufLen : %d\n", strlen(buf));
         //printf("resultLen : %d\n", strlen(result));
         //printf("return fp : %d\n\n", -strlen(buf)+(pos_end-buf));

      }

      memset(buf, 0, sizeof(buf));
      memset(result, 0, sizeof(result));
   }

   printf("=============== Crawling done... ===============\n");
   printf("   Toal URLs: %d\n", cnt);
}
