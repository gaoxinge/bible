#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define echoServIP "127.0.0.1"
#define echoServPort 54321
#define RCVBUFSIZE 1024


void DieWithError(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}


int main() {
    int clientSock;
    if ((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    struct sockaddr_in echoServAddr;
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(echoServIP);
    echoServAddr.sin_port = htons(echoServPort);

    if (connect(clientSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    char *echoStrings[] = {"Hello", "World", "Hello World"};
    for (int i = 0; i < 3; i++) {
        char *echoString = echoStrings[i];
        int echoStringLen = strlen(echoString);
        if (send(clientSock, echoString, echoStringLen, 0) != echoStringLen)
            DieWithError("send() sent a different number of bytes than excepted");

        int n;
        char echoBuffer[RCVBUFSIZE];
        if ((n = recv(clientSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
           DieWithError("recv failed()");
        echoBuffer[n] = '\0';
        printf("%s\n", echoBuffer);
    }

    close(clientSock);
    return 0;
}