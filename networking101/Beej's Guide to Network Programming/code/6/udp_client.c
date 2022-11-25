#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void DieWithError(char *str) {
    perror(str);
    exit(-1);
}

int CreateUDPClient() {
    int clientSock;
    if ((clientSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");
    return clientSock;
}

int main() {
    int clientSock = CreateUDPClient();
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(4950);
    if (sendto(clientSock, "hello world", 11, 0, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        DieWithError("sendto() failed");
    
    close(clientSock);
    return 0;
}
