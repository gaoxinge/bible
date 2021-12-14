#include <stdio.h>
#include <stdlib.h>

#include "backward.hpp"
namespace backward{
    backward::SignalHandling sh;
}

int main(){
    char *c = "hello world";
    c[1] = 'H';
    return 0;
}
