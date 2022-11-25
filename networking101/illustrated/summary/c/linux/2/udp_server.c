#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define echoServPort 54321
#define ECHOMAX 1024


void DieWithError(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}


int main() {
    int servSock;
    if ((servSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    struct sockaddr_in echoServAddr;
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    for (;;) {
        struct sockaddr_in echoClientAddr;
        socklen_t clientAddrLen = sizeof(echoClientAddr);

        int recvMsgSize;
        char echoBuffer[ECHOMAX];
        if ((recvMsgSize = recvfrom(servSock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &echoClientAddr, &clientAddrLen)) < 0)
            DieWithError("recvfrom() failed");

        if (sendto(servSock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClientAddr, sizeof(echoClientAddr)) != recvMsgSize)
            DieWithError("send() failed");
    }
    return 0;
}