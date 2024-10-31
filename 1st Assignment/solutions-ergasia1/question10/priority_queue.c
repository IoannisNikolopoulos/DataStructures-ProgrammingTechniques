#include <stdlib.h>

struct node {
	int data;            
	struct node *next;  
};

typedef struct node Node;
typedef Node* NodePtr;

NodePtr createNode(int incomingData) {
	NodePtr newNode = malloc(sizeof(Node));
	newNode->data = incomingData;            
	newNode->next = NULL;                    
	return newNode;                           
}

struct priority_queue {
	NodePtr head;   // Pointer to the head of the priority queue
	int elements;   // Number of elements in the priority queue
};
typedef struct priority_queue *PriorityQueue;

int PQSize(PriorityQueue pq) {
	return pq->elements;  // Return the number of elements in the priority queue
}

int PQEmpty(PriorityQueue pq) {
	return pq->elements == 0;  // Return 1 if the priority queue is empty, 0 otherwise
}

PriorityQueue PQCreate() {
	PriorityQueue pq = malloc(sizeof(struct priority_queue));  // Allocate memory for the priority queue
	pq->head = NULL;                                          // Initialize head pointer to NULL
	pq->elements = 0;                                         // Initialize number of elements to 0
	return pq;                                                // Return the new priority queue
}

void PQInsert(PriorityQueue pq, int data) {
	NodePtr newNode = createNode(data);  // Create a new node with the given data

	NodePtr cursor;
	// Traverse the priority queue until reaching the end or finding a node with data greater than or equal to the new data
	for (cursor = pq->head; cursor->next != NULL || cursor->next->data >= data; cursor = cursor->next);

	newNode->next = cursor->next;  // Set the next pointer of the new node to the next node of the cursor
	cursor->next = newNode;        // Set the next pointer of the cursor to the new node
}

int PQRemove(PriorityQueue pq) {
	if (PQEmpty(pq)) return -1;  // If the priority queue is empty, return -1

	NodePtr head = pq->head;        // Store the head node of the priority queue temporarily
	pq->head = pq->head->next;      // Move the head pointer to the next node
	int data = head->data;          // Get the data of the head node
	free(head);                     // Free memory allocated for the head node
	return data;                    // Return the data of the removed node
}
