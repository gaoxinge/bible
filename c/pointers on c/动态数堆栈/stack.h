#define STACK_TYPE int

void create_stack(int size);
void destroy_stack();
void push(STACK_TYPE value);
void pop();
STACK_TYPE top();
int is_empty();
int is_full();