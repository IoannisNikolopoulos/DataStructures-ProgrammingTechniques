#include <stdio.h>
#include <stdlib.h>

typedef struct BSTnode* Data;
typedef struct deque* Deque;

Deque createDeque();
int dequeIsEmpty(Deque deque);
int dequeSize(Deque deque);
void dequePush(Deque deque, Data data);
void dequeEnque(Deque deque, Data data);
Data dequePop(Deque deque);
Data dequeDequeue(Deque deque);
