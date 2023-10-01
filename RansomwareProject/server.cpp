#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32")
#include <Windows.h>
#include <ctime> // Include the <ctime> header for time-related functions

using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    // Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket
    SOCKADDR_IN serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // You can choose any port you like
    serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Socket binding failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "Socket listening failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server is listening for incoming connections..." << endl;

    // Accept a connection from the client
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

    // Generate a random key
    unsigned char randomKey[8];
    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator with the current time
    for (int i = 0; i < 8; i++) {
        randomKey[i] = rand() % 256;
    }

    // Send the key to the client
    int bytesSent = send(clientSocket, (const char*)randomKey, sizeof(randomKey), 0);
    if (bytesSent == SOCKET_ERROR) {
        cout << "Key sending failed" << endl;
    }
    else {
        cout << "Key sent successfully" << endl;
        cout << "Key: ";
        for (int i = 0; i < sizeof(randomKey); i++) {
            printf("%02x ", randomKey[i]);
        }
        cout << endl;

    }

    // Close sockets and cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
