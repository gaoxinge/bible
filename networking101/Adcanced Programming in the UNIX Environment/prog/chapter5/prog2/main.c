#include <stdio.h>
#include <string.h>
#include "sds.h"

#define BUFFSIZE 3

sds ffgets(sds s, FILE *fp) {
    s[0] = '\0';
    sdsupdatelen(s);
    
    char buf[BUFFSIZE];
    while (fgets(buf, BUFFSIZE, fp) != NULL) {
        s = sdscat(s, buf);
        if (s[sdslen(s) - 1] == '\n') 
            break;
    }
    
    return s;
}

int main() {
    sds s = sdsempty();
    int line = 1;
    while (strcmp(s = ffgets(s, stdin), "") != 0) {
        printf("%d %s", line, s);
        line += 1;
    }
    sdsfree(s);
    return 0;
}