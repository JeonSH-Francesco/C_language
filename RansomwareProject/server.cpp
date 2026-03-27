#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32")
#include <Windows.h>
#include <ctime>
using namespace std;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN serverAddr = { 0 };
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Socket binding failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "Socket listening failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server is listening for incoming connections..." << endl;

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Connection acceptance failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 16바이트 키 생성 (AES-128)
    unsigned char randomKey[16];
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 16; i++) {
        randomKey[i] = rand() % 256;
    }

    // 16바이트 키 전송
    int bytesSent = send(clientSocket, (const char*)randomKey, sizeof(randomKey), 0);
    if (bytesSent == SOCKET_ERROR) {
        cout << "Key sending failed" << endl;
    }
    else {
        cout << "Key sent successfully" << endl;
        cout << "Key: ";
        for (int i = 0; i < (int)sizeof(randomKey); i++) {
            printf("%02x ", randomKey[i]);
        }
        cout << endl;
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
