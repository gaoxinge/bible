#ifndef VALUE_H
#define VALUE_H

void* new(const void* type, ...);
void exec(const void* tree);
void delete(void* tree);

const void* Add;
const void* Sub;
const void* Mul;
const void* Div;
const void* Minus;
const void* Value;

void* sum();
void* product();
void* factor();

void process(const void* tree);
#endif