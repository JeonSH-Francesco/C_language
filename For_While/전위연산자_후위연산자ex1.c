#include <stdio.h>

int main() {
    int i;

    printf("Using for loop:\n");
    for (i = 0; i < 3; i++) {
        printf("i = %d\n", i);
    }

    printf("Using ++i:\n");
    i = 0;
    while (i < 3) {
        printf("i = %d\n", ++i);
    }

    return 0;
}
