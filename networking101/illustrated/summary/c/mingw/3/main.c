#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT 5154
#define RCVBUFSIZE 1024

int main(int argc, char *argv[]) {
    WSADATA Ws;
    if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0) {
        printf("start up error");
        return -1;
    }
    
    struct sockaddr_in ServerAddr;
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(PORT);
    
    int ClientSocket;
    if ((ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("socket() failed");
        return -1;
    }
    
    if ((connect(ClientSocket, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr))) < 0) {
        printf("connect() failed");
        return -1;
    }
    
    char *SendBuffers[] = {"Hello", "World", "Hello World"};
    for (int i = 0; i < 3; i++) {
        char *SendBuffer = SendBuffers[i];
        int SendBufferLen = strlen(SendBuffer);
        if (send(ClientSocket, SendBuffer, SendBufferLen, 0) != SendBufferLen) {
            printf("send() failed");
            return -1;
        }
        
        int n;
        char echoBuffer[RCVBUFSIZE];
        if ((n = recv(ClientSocket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
            printf("recv() failed");
            return -1;
        }
        echoBuffer[n] = '\0';
        printf("%s\n", echoBuffer);
    }
    
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}