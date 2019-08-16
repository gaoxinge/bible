#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define MAXPENDING 5

void DieWithError(char *errorMessage);
int CreateTCPServerSocket(char* port);
int AcceptTCPConnection(int servSock);
void HandleTCPClient(int clntSocket);
void SigchldHandler(int signalType);

int main(int argc, char *argv[]) {
    pid_t processID;
    
    struct sigaction sa;
    sa.sa_handler = SigchldHandler;
    if (sigemptyset(&sa.sa_mask) < 0)
        DieWithError("sigemptyset() failed");
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) < 0)
        DieWithError("sigaction() failed");
    
    int servSock = CreateTCPServerSocket("3490");
    for (;;) {
        int clntSock = AcceptTCPConnection(servSock);
        
        if ((processID = fork()) < 0) {
            DieWithError("fork() failed");
        } else if (processID == 0) {
            close(servSock);
            HandleTCPClient(clntSock);
            exit(0);
        } else {
            close(clntSock);
        }
    }
    
    return 0;
}

void DieWithError(char *errorMessage) {
    perror(errorMessage);
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
    char s[INET6_ADDRSTRLEN];
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
        DieWithError("accept() failed");
    inet_ntop(echoClntAddr.sin_family, &(echoClntAddr.sin_addr), s, sizeof(s));
    printf("server: got connection from %s\n", s);
    return clntSock;
}

void HandleTCPClient(int clntSocket) {
    if (send(clntSocket, "Hello, world", 13, 0) < 0)
        DieWithError("send() failed");
    close(clntSocket);
}

void SigchldHandler(int signalType) {
    int saved_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}
