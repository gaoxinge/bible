#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define RCVBUFSIZE 1024


void DieWithError(char *str) {
    fprintf(stderr, "%s\n", str);
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
    char *echoStrings[] = {"Hello", "World", "Hello World"};
    for (int i = 0; i < 3; i++) {
        char *echoString = echoStrings[i];
        int echoStringLen = strlen(echoString);
        if (send(clientSock, echoString, echoStringLen, 0) != echoStringLen)
            DieWithError("send() send a different number of bytes than excepted");

        int n;
        char echoBuffer[RCVBUFSIZE];
        if ((n = recv(clientSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv failed()");
        echoBuffer[n] = '\0';
        printf("%s\n", echoBuffer);
    }

    close(clientSock);
  
}

int main() {
    int clientSock = CreateTCPClntSocket("127.0.0.1", 54321);
    HandleTCPServer(clientSock);
    return 0;
}
