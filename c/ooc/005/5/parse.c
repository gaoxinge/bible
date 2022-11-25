#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "error.h"

enum tokens token;
double number;

enum tokens scan(const char* buf) {
    static const char* bp;
    
    if (buf)
        bp = buf;
    
    while (isspace(*bp))
        ++bp;
    
    if (isdigit(*bp) || *bp == '.') {
        errno = 0;
        token = NUMBER, number = strtod(bp, (char **) &bp);
        if (errno == ERANGE)
            error("bad value: %s", strerror(errno));
    } else {
        token = *bp ? *bp++ : 0;
    }
    return token;
}