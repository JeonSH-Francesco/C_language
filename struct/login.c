#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct PasswordManager {
	char Id[20];
	char pw[20];
} pwm;


int createUser(pwm *p,int numUsers) {
	if (numUsers > 20) {
		printf("The maximum number of users has been reached.\n");
		return;
	}
	char user_id[20];

	printf("Enter user ID (5 to 19 characters): ");
	scanf("%s", user_id);

	for (int i = 0; i < numUsers; i++) {
		if (strcmp(p[i].Id, user_id) == 0) {
			printf("The user is already activated.\n");
			return numUsers;
		}
	}
	strncpy(p[numUsers].Id, user_id, sizeof(p[numUsers].Id) - 1);
	

	for (int i = 0; i < numUsers; i++) {
		if (strcmp(p[i].Id, p[numUsers].Id) == 0) {
			printf("The user is already activated");
			return;
		}
	}
	printf("Enter password (5 to 19 characters): ");
	scanf("%s", p[numUsers].pw);
	

	printf("%d", numUsers);
	printf("User created successfully.\n");
	return numUsers+1;
}

void login(pwm *p,int numUsers) {
	char user_id[20] = "";
	char pw[20] = "";
	int trg = 0;

	if (numUsers == 0) {
		printf("The database is empty.");
		return;
	}

	printf("Input User Id :");
	scanf("%s", user_id);

	printf("Input User pw :");
	scanf("%s", pw);
	


	for (int i = 0; i < numUsers; i++) {
		if (strcmp(p[i].Id, user_id) == 0 && strcmp(p[i].pw, pw) == 0) {
			printf("%s is login.\n", p[i].Id);
			return 1;
		}
		

	}
	printf("login failed.\n");
	return 0; 
}

void display(pwm *p,int numUsers) {
	for (int i = 0; i < numUsers; i++) {
		printf("%s\n",p[i].Id);
	}
}


int main() {
	pwm p[20];
	int num = 0;
	int numUsers = 0;
	int index = 0;
	
	do {
		printf("Input Number (1. Create User / 2. Login / 3. Display Current Users / 4. Exit): ");
		scanf("%d", &num);

		switch (num) {
		case 1:
			numUsers=createUser(p,numUsers);
			break;
			case 2:
				login(p,numUsers);
				break;
			case 3:
				display(p,numUsers);
				break;
			case 4:
				printf("Program exited.\n");
				break;
		default:
			printf("Invalid input. Please try again.\n");
			break;
		}
	} while (num != 4);

	return 0;
}
