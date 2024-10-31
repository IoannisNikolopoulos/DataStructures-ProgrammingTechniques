#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque* Deque;

Deque createDeque();
int dequeIsEmpty(Deque deque);
int dequeSize(Deque deque);
void dequePush(Deque deque, int data);
void dequeEnque(Deque deque, int data);
int dequePop(Deque deque);
int dequeDequeue(Deque deque);
void dequePrint(Deque deque);

#endif /* DEQUE_H */
