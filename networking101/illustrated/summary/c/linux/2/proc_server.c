#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);
int CreateTCPServerSocket(char* port);
int AcceptTCPConnection(int servSock);
void HandleTCPClient(int clntSocket);

int main(int argc, char *argv[]) {
    int servSock;
    int clntSock;
    
    
    pid_t processID;
    unsigned int childProcCount = 0;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(-1);
    }
    
    servSock = CreateTCPServerSocket(argv[1]);
    
    for (;;) {
        clntSock = AcceptTCPConnection(servSock);
        
        if ((processID = fork()) < 0) {
            DieWithError("fork() failed");
        } else if (processID == 0) {
            close(servSock);
            HandleTCPClient(clntSock);
            exit(0);
        }
        
        close(clntSock);
        childProcCount++;
        
        while (childProcCount) {
            processID = waitpid((pid_t) -1, NULL, WNOHANG);
            if (processID < 0)       DieWithError("...");
            else if (processID == 0) break;
            else                     childProcCount--;
        }
    }
}

void DieWithError(char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
    exit(-1);
}

int CreateTCPServerSocket(char* port) {
    int servSock;
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    
    struct sockaddr_in echoServAddr;
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(atoi(port));
    
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");
    
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    
    return servSock;
}

int AcceptTCPConnection(int servSock) {
    int clntSock;
    struct sockaddr_in echoClntAddr;
    unsigned int clntLen = sizeof(echoClntAddr);
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
        DieWithError("accept() failed");
    printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
    return clntSock;
}

void HandleTCPClient(int clntSocket) {
    char echoBuffer[RCVBUFSIZE];
    int recvMsgSize;
    
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    
    while (recvMsgSize > 0) {
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");
        
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }
    
    close(clntSocket);
}