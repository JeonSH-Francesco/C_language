#include <stdio.h>
char pw[5] = "Sdev";

int main() {
	
	char key[5]="aaaa";
	int i = 0;
	int j = 0;

	for (i = 0; i <4; i++) {
		for (j = 'A'; j <='z'; j++) {
			if ((char)j == pw[i]) {
				key[i] = (char)j;
			}
		}
	}
	printf("Brute force success! Password found: %s\n", key);

	return 0;
	
}
