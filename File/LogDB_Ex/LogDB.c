#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define MAX_LOG_ENTRIES 100

typedef struct logDB{
	char timestamp1[100];
	char timestamp2[100];
	char username[100];
	char password[100];
	char status[100];
} LogEntry;


void timestampDB(LogEntry* le) {
	FILE* fp;
	char line[100];
	char ansSuccess[8] = "SUCCESS";
	char ansError[6] = "ERROR";
	int successCount = 0;
	int errorCount = 0;

	fp = fopen("log.txt", "r");
	if (fp == NULL) {
		printf("No File.\n");
		return;
	}

	printf("----------------------\n");
	printf("Login Success UserDB\n");
	printf("----------------------\n");

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansSuccess) != NULL) {
			sscanf(line, "%s", le[successCount].timestamp1);
			sscanf(line, "%*s %s", le[successCount].timestamp2);

			printf("TimeStamp YYYY-MM-DD[%d] : %s\n", successCount + 1, le[successCount].timestamp1);
			printf("TimeStamp HH:MM:SS[%d] : %s\n", successCount + 1, le[successCount].timestamp2);
			printf("-----------\n");

			successCount++;
		}
	}
	
	fseek(fp, 0, SEEK_SET);

	printf("----------------------\n");
	printf("Login ERROR UserDB\n");
	printf("----------------------\n");

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansError) != NULL) {
			sscanf(line, "%s", le[successCount+ errorCount].timestamp1);
			sscanf(line, "%*s %s", le[successCount+ errorCount].timestamp2);

			printf("TimeStamp YYYY-MM-DD[%d] : %s\n", successCount+ errorCount + 1, le[successCount+ errorCount].timestamp1);
			printf("TimeStamp HH:MM:SS[%d] : %s\n", successCount+ errorCount + 1, le[successCount+ errorCount].timestamp2);
			printf("-----------\n");

			errorCount++;
		}
	}

	fclose(fp);
}

void usernameDB(LogEntry* le) {
	FILE* fp;
	char line[100];
	char ansSuccess[8] = "SUCCESS";
	char ansError[6] = "ERROR";
	int successCount = 0;
	int errorCount = 0;

	fp = fopen("log.txt", "r");
	if (fp == NULL) {
		printf("No File.\n");
		return;
	}

	printf("----------------------\n");
	printf("Login Success UserDB\n");
	printf("----------------------\n");

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansSuccess) != NULL) {
			sscanf(line, "%*s %*s %s", le[successCount].username);
			sscanf(line, "%*s %*s %*s %s", le[successCount].password);

			printf("username[%d] : %s\n", successCount + 1, le[successCount].username);
			printf("password[%d] : %s\n", successCount + 1, le[successCount].password);
			printf("-----------\n");

			successCount++;
		}
	}
	
	fseek(fp, 0, SEEK_SET);

	printf("----------------------\n");
	printf("Login ERROR UserDB\n");
	printf("----------------------\n");

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansError) != NULL) {
			sscanf(line, "%*s %*s %s", le[successCount + errorCount].username);
			sscanf(line, "%*s %*s %*s %s", le[successCount + errorCount].password);

			printf("username[%d] : %s\n", successCount + errorCount + 1, le[successCount + errorCount].username);
			printf("password[%d] : %s\n", successCount + errorCount + 1, le[successCount + errorCount].password);
			printf("-----------\n");

			errorCount++;
		}
	}

	fclose(fp);
}

void statusDB(LogEntry* le) {
	FILE* fp;
	char line[MAX_LOG_ENTRIES + 1];
	char ansSuccess[8] = "SUCCESS";
	char ansError[6] = "ERROR";

	int successCount = 0;
	int errorCount = 0;

	fp = fopen("log.txt", "r");
	if (fp == NULL) {
		printf("No File.\n");
		return 1;
	}


	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansSuccess) != NULL) {
			sscanf(line, "%*s %*s %*s %*s %s", le[successCount].status);

			printf("Status[%d] : %s\n", successCount + 1, le[successCount].status);
			printf("-----------\n");

			successCount++;
		}
	}
	
	fseek(fp, 0, SEEK_SET);

	printf("----------------------\n");
	printf("Login ERROR UserDB\n");
	printf("----------------------\n");

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, ansError) != NULL) {
			sscanf(line, "%*s %*s %*s %*s %s", le[successCount+errorCount].status);

			printf("status[%d] : %s\n", successCount + errorCount + 1, le[successCount + errorCount].status);
			printf("-----------\n");

			errorCount++;
		}
	}

	printf("----------------------\n");
	printf("Status DB display\n");
	printf("----------------------\n");
	printf("SUCCESS : %d\n", successCount);
	printf("ERROR : %d\n", errorCount);
	printf("----------------------\n");
	
	fclose(fp);

}

int main() {
	int num = 0;
	
	LogEntry* le;

	le = (LogEntry*)malloc(sizeof(LogEntry) * MAX_LOG_ENTRIES);
	memset(le, 0x0, sizeof(LogEntry));

	do {
		printf("------------------------------\n");
		printf("Login Log Database Main Menu\n");
		printf("------------------------------\n");
		printf("1. Display Timestamp Database\n");
		printf("2. Display Username and Password Database\n");
		printf("3. Display Status Database\n");
		printf("4. Exit\n");
		printf("------------------------------\n");
		printf("Enter a choice (1/2/3/4): ");
		scanf("%d", &num);
		system("cls");

		switch (num) {
		case 1 :
			timestampDB(le);
			system("pause");
			system("cls");
			break;
		case 2:
			usernameDB(le);
			system("pause");
			system("cls");
			break;
		case 3:
			statusDB(le);
			system("pause");
			system("cls");
			break;
		case 4:
			printf("Program exited.\n");
			system("pause");
			system("cls");
			break;
		default:
			printf("Invalid input. Please try again.\n");
			Sleep(2000);
			system("cls");
			break;
		}


	} while (num!=4);


	free(le);

	return 0;
}
