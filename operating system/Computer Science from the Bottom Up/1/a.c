#include <stdio.h>

struct greet_api
{
    int (*say_hello)(char *name);
    int (*say_goodbye)(void);
};

int say_hello_fn(char *name)
{
    printf("Hello %s\n", name);
    return 0;
}

int say_goodbye_fn(void)
{
    printf("Goodbye\n");
    return 0;
}

struct greet_api greet_api =
{
    .say_hello = say_hello_fn,
    .say_goodbye = say_goodbye_fn
};

int main(int argc, char *argv[])
{
    greet_api.say_hello("1234");
    greet_api.say_goodbye();
    printf("%p, %p, %p\n", greet_api.say_hello, say_hello_fn, &say_hello_fn);
    return 0;
}