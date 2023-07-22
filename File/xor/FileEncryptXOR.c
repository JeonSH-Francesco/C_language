#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 파일 암호화 함수
void encryptFile(const char* inputFileName, const char* outputFileName, unsigned char key) {
	FILE* inputFile = fopen(inputFileName, "rb");
	FILE* outputFile = fopen(outputFileName, "wb");

	if (inputFile == NULL || outputFile == NULL) {
		printf("Error: Failed to open file.\n");
		return;
	}

	char ch;
	while ((ch = fgetc(inputFile)) != EOF) {
		// XOR 연산을 통해 암호화
		ch ^= key;
		fputc(ch, outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);
}

// 파일 복호화 함수
void decryptFile(const char* inputFileName, const char* outputFileName, unsigned char key) {
	encryptFile(inputFileName, outputFileName, key);  // XOR 연산에 의해 복호화와 암호화는 동일하다.
	printf("Decryption complete.\n");
}

int main() {
	const char* inputFileName = "file.txt";      // 원본 파일명
	const char* encryptedFileName = "encrypted.txt";    // 암호화된 파일명
	const char* decryptedFileName = "decrypted.txt";    // 복호화된 파일명

	unsigned char key = 0x5A;   // 암호화 및 복호화에 사용할 키 값

	// 파일 암호화
	encryptFile(inputFileName, encryptedFileName, key);
	printf("Encryption complete.\n");
	
	// 파일 복호화
	decryptFile(encryptedFileName, decryptedFileName, key);

	return 0;
}
