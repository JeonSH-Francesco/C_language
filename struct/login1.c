#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LENGTH 20
struct Password {
	char password[MAX_LENGTH + 1];
	bool isValid;
};

// 계정 구조체
typedef struct Account {
	char Id[MAX_LENGTH + 1];
	struct Password password;
}account;

bool isValidatePassword(const char* password) {
	int length = strlen(password);
	bool has_special = false;
	bool has_number = false;
	bool has_lower = false;
	bool has_upper = false;

	if (length < 5 || length > 20) {
		return false;
	}

	for (int i = 0; password[i] != '\0'; i++) {
		if (islower(password[i])) {
			has_lower = true;
		}
		else if (isupper(password[i])) {
			has_upper = true;
		}
		else if (isdigit(password[i])) {
			has_number = true;
		}
		else if (ispunct(password[i])) {
			has_special = true;
		}
	}

	return (has_special && has_number && has_lower && has_upper);
}


int createUser(account* ac, int numUsers) {
	if (numUsers >= 20) {
		printf("The maximum number of users has been reached.\n");
		return numUsers;
	}

	char user_id[MAX_LENGTH + 1];

	printf("Enter user ID (5 to 19 characters): ");
	scanf("%s", user_id);

	for (int i = 0; i < numUsers; i++) {
		if (strcmp(ac[i].Id, user_id) == 0) {
			printf("The user is already activated.\n");
			return numUsers;
		}
	}

	strncpy(ac[numUsers].Id, user_id, sizeof(ac[numUsers].Id) - 1);

	char password[MAX_LENGTH + 1];

	do {
		printf("Enter password (5 to 19 characters): ");
		scanf("%s", password);

		if (!isValidatePassword(password)) {
			printf("Invalid password. Please make sure it contains at least one special character, one number, one lowercase letter, and one uppercase letter.\n");
		}
	} while (!isValidatePassword(password));

	strncpy(ac[numUsers].password.password, password, sizeof(ac[numUsers].password.password) - 1);
	ac[numUsers].password.isValid = true;

	printf("User created successfully.\n");
	return numUsers + 1;
}


void login(account* ac, int numUsers) {
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
		if (strcmp(ac[i].Id, user_id) == 0 && strcmp(ac[i].password.password, pw) == 0) {
			printf("%s is login.\n", ac[i].Id);
			printf("Login Success!\n");
			return 1;
		}

	}

	printf("Login failed.\n");
	return 0;
}

void display(account* ac, int numUsers) {
	for (int i = 0; i < numUsers; i++) {
		printf("%s\n", ac[i].Id);
	}
}


int main() {
	account ac[20];
	int num = 0;
	int numUsers = 0;
	int index = 0;

	do {
		printf("Input Number (1. Create User / 2. Login / 3. Display Current Users / 4. Exit): ");
		scanf("%d", &num);

		switch (num) {
		case 1:
			numUsers = createUser(ac, numUsers);
			break;
		case 2:
			login(ac, numUsers);
			break;
		case 3:
			display(ac, numUsers);
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
