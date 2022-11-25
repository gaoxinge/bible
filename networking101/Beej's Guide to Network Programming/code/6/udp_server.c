#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void DieWithError(char *str) {
    perror(str);
    exit(-1);
}

int CreateUDPServer(int port) {
    int serverSock;
    if ((serverSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        DieWithError("bind() failed");
    
    return serverSock;
}

int main() {
    int serverSock = CreateUDPServer(4950);
    
    int n;
    char buf[11];
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    if ((n = recvfrom(serverSock, buf, 11, 0, (struct sockaddr *) &clientAddr, &clientLen)) < 0)
        DieWithError("recvfrom() failed");
    buf[n] = '\0';
    
    char s[INET6_ADDRSTRLEN];
    inet_ntop(clientAddr.sin_family, &(clientAddr.sin_addr), s, sizeof(s));
    printf("listener: got packet from %s\n", s);
    printf("listener: packet contains %s\n", buf);
    
    close(serverSock);
    return 0;
}
