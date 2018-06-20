#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int ret = -1;
    char* ptr = malloc(sizeof(char) * 128);
    if (ptr == NULL) {
        perror("malloc get error");
        goto exit;
    }
    strcpy(ptr, "KerKer");
    printf("%s\n", ptr);
    ret = 0;
exit:
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
    return ret;
}