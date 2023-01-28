#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_LEN 80
#define MAX_SENTENCE_LEN 1024
#define INPUT_FILE_NAME "sample_text.txt"


int main() {
    FILE *ifp;
    char *buf = (char*)malloc(sizeof(char)*MAX_BUFFER_LEN);
    char *sentence = (char*)malloc(sizeof(char)*MAX_SENTENCE_LEN);
    char *pos;
    ifp = fopen(INPUT_FILE_NAME, "r");
    memset(sentence, 0x0, MAX_BUFFER_LEN);

    while (!feof(ifp)) {
        memset(buf, 0x0, MAX_BUFFER_LEN);
        fgets(buf, MAX_BUFFER_LEN, ifp);
        if ((pos = strchr(buf, '.')) != NULL) {
            if (strlen(sentence) == 0) {
                strncpy(sentence, buf, strstr(buf, pos)-buf+1);
            }
            else {
                strncat(sentence, buf, strstr(buf, pos)-buf+1);
            }
        printf("%s\n", sentence);

        if ((strstr(buf, pos) - buf) != 0) {
        printf("%s", buf+(strstr(buf, pos)-buf+1));
        }
        memset(sentence, 0x0, MAX_SENTENCE_LEN);
        }

        else {
        strncat(sentence, buf, strlen(buf));
        }
    }

    printf("\n\nfile read done.\n");
    free(buf);
    free(sentence);
    fclose(ifp);

    return 0;

}
