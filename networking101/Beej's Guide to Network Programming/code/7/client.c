#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void DieWithError(char *str) {
    perror(str);
    exit(-1);
}

int CreateTCPClntSocket(char *host, unsigned short port) {
    int clientSock;
    if ((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    struct sockaddr_in echoServAddr;
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(host);
    echoServAddr.sin_port = htons(port);
    
    if (connect(clientSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    return clientSock;
}

void HandleTCPServer(int clientSock) {
    if (send(clientSock, "hello world", 11, 0) < 0)
        DieWithError("send() failed");
    close(clientSock);
}

int main() {
    int clientSock = CreateTCPClntSocket("127.0.0.1", 9034);
    HandleTCPServer(clientSock);
    return 0;
}