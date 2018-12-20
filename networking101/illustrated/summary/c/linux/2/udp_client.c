#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define echoClientPort 12345
#define echoServIP "127.0.0.1"
#define echoServPort 54321
#define ECHOMAX 1024


void DieWithError(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}


int main() {
    int clientSock;
    if ((clientSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    struct sockaddr_in echoClientAddr;
    echoClientAddr.sin_family = AF_INET;
    echoClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoClientAddr.sin_port = htons(echoClientPort);

    if (bind(clientSock, (struct sockaddr *) &echoClientAddr, sizeof(echoClientAddr)) < 0)
        DieWithError("connect() failed");

    struct sockaddr_in echoServAddr;
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(echoServIP);
    echoServAddr.sin_port = htons(echoServPort);
    socklen_t echoServAddrLen = sizeof(echoServAddr);

    char *echoString = "hello world";
    int echoStringLen;
    echoStringLen = strlen(echoString);
    if (sendto(clientSock, echoString, echoStringLen, 0, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
        DieWithError("send() sent a different number of bytes than expected");

    int n;
    char echoBuffer[ECHOMAX];
    if ((n = recvfrom(clientSock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &echoServAddr, &echoServAddrLen)) < 0)
        DieWithError("recvfrom() failed");
    echoBuffer[n] = '\0';
    printf("%s\n", echoBuffer);

    close(clientSock);
    return 0;
}