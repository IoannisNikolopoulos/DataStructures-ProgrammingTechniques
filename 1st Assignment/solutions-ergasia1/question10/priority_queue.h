typedef struct priority_queue *PriorityQueue;

PriorityQueue PQCreate();
void PQInsert(PriorityQueue pq, int data);
int PQRemove(PriorityQueue pq);
int PQSize(PriorityQueue pq);
int PQEmpty(PriorityQueue pq);
