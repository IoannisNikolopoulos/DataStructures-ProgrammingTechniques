#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef int Item;

typedef struct priority_queue {
	int Count;
	Item *ItemArray;
} PriorityQueue;

typedef PriorityQueue* PQPointer;
PQPointer QUEUEinit(int maxN);
int QUEUEempty(PQPointer);
void QUEUEput(PQPointer, Item);
Item QUEUEget(PQPointer);

#endif // PRIORITY_QUEUE_H
