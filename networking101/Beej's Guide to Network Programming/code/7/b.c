#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);
int CreateTCPServerSocket(unsigned short echoServPort);
int AcceptTCPConnection(int servSock);
int HandleTCPClient(int clntSocket);

int main() {
    fd_set master;
    fd_set read_fds;
    int listener;
    int new_fd;
    int fd_max;
    
    listener = CreateTCPServerSocket(9034);
    fd_max = listener;
    
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(listener, &master);

    for (;;) {
        read_fds = master;
        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) < 0)
            DieWithError("select() failed");
        
        for (int i = 0; i < fd_max + 1; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener) {
                    int new_fd = AcceptTCPConnection(listener);
                    FD_SET(new_fd, &master);
                    if (new_fd > fd_max) fd_max = new_fd;
                } else {
                    if (!HandleTCPClient(i)) {
                        close(i);
                        FD_CLR(i, &master);
                    }
                }
            }
        }
    }
    
    return 0;
}

void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(-1);
}

int CreateTCPServerSocket(unsigned short echoServPort) {
    int servSock;
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    
    struct sockaddr_in echoServAddr;
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);
    
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

int HandleTCPClient(int clntSocket) {
    char echoBuffer[RCVBUFSIZE];
    
    int recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0);
    if (recvMsgSize < 0)
        DieWithError("recv() failed");
    else if (recvMsgSize == 0)
        return 0;
    
    echoBuffer[recvMsgSize] = '\0';
    printf("%s\n", echoBuffer);
    return 1;
}