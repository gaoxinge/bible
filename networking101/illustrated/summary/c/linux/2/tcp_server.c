#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define echoServPort 54321
#define MAXPENDING 5
#define RCVBUFSIZE 1024


void DieWithError(char *str) {
    fprintf(stderr, "%s\n", str);
    exit(-1);
}


int main() {
    int servSock;
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    struct sockaddr_in echoServAddr;
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");


    for (;;) {
        struct sockaddr_in echoClntAddr;
        socklen_t clntLen = sizeof(echoClntAddr);
        int clntSock;
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");

        int recvMsgSize;
        char echoBuffer[RCVBUFSIZE];
        if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");

        while (recvMsgSize > 0) {
            if (send(clntSock, echoBuffer, recvMsgSize, 0) != recvMsgSize)
                DieWithError("send() failed");

            if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
                DieWithError("recv() failed");
        }

        close(clntSock);
    }

    return 0;
}