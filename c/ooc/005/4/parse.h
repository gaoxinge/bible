#ifndef PARSE_H
#define PARSE_H
#define NUMBER '1'

enum tokens {NUM=NUMBER};
enum tokens token;
double number;
enum tokens scan(const char* buf);

#endif