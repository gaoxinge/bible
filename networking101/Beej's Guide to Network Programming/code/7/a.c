#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval tv;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    
    select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
    
    if (FD_ISSET(STDIN_FILENO, &readfds))
        printf("A key was pressed!\n");
    else
        printf("Timed out.\n");
    
    return 0;
}