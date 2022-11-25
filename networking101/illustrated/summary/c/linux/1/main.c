#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define PORT 54321
#define BACKLOG 5

int setup_sock(int port) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    
    bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listen_fd, BACKLOG);
    
    return listen_fd;
}

void echo_request(int conn_fd) {
    int n;
    time_t ticks;
    
    char sendBuff[BUFFER_SIZE];
    char recvBuff[BUFFER_SIZE];
    memset(sendBuff, 0, sizeof(sendBuff));
    memset(recvBuff, 0, sizeof(recvBuff));
    
    while ((n = recv(conn_fd, recvBuff, sizeof(recvBuff), 0)) > 0) {
        recvBuff[n] = '\0';
        printf("received: %s\n", recvBuff);
        
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s: ", ctime(&ticks));
        strcat(sendBuff, recvBuff);
        send(conn_fd, sendBuff, strlen(sendBuff), 0);
    }
    
    printf("received 0 bytes, close.\n");
    close(conn_fd);
}

int main(int argc, char *argv[]) {
    int listen_fd = setup_sock(PORT);
    printf("start server...\n");
    printf("listening on 0.0.0.0 %d...\n", PORT);
    
    struct sockaddr_in cli_addr;
    memset(&cli_addr, '0', sizeof(cli_addr));
    socklen_t cli_len;
    cli_len = sizeof(cli_addr);
    
    while (1) {
        int conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);
        printf("client ip: %s, port: %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        echo_request(conn_fd);
    }
    
    return 0;
}