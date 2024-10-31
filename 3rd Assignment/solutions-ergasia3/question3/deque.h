#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>

#include "directed_graph.h"

typedef Vertex Data;
typedef struct deque* Deque;

Deque createDeque();
int dequeIsEmpty(Deque deque);
int dequeSize(Deque deque);
void dequePush(Deque deque, Data data);
void dequeEnque(Deque deque, Data data);
Data dequePop(Deque deque);
Data dequeDequeue(Deque deque);
void dequeDelete(Deque deque);

#endif // DEQUE_H
