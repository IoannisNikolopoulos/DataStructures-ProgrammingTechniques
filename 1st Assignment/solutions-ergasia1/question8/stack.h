#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;
Stack createStack();
void stackPush(Stack stack, char* c);
char* stackPop(Stack stack);

#endif //STACK_H