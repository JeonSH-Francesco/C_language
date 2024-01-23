#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock\n");
        return 1;
    }

    char hostname[100];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        struct addrinfo* result = NULL;
        struct addrinfo* ptr = NULL;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if (getaddrinfo(hostname, NULL, &hints, &result) == 0) {
            for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                if (ptr->ai_family == AF_INET) {
                    struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
                    char ipstr[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipstr, sizeof(ipstr));
                    printf("Local IP Address: %s\n", ipstr);
                    break;  // 첫 번째 매치를 사용
                }
            }

            freeaddrinfo(result);
        }
    }

    WSACleanup();
    return 0;
}
