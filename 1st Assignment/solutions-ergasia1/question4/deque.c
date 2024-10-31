#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
struct node {
	int data;            // Data stored in the node
	struct node *next;   // Pointer to the next node
	struct node *prev;   // Pointer to the previous node
};

typedef struct node Node;
typedef Node* NodePtr;

NodePtr createNode(int incomingData) {
	NodePtr newNode = malloc(sizeof(Node));  // Allocate memory for the new node
	newNode->data = incomingData;            // Set the data of the new node
	newNode->next = NULL;                    // Initialize next pointer to NULL
	newNode->prev = NULL;                    // Initialize previous pointer to NULL
	return newNode;                          // Return the new node
}

struct deque {
	NodePtr head;    // Pointer to the head of the deque
	NodePtr tail;    // Pointer to the tail of the deque
	int elements;    // Number of elements in the deque
};

typedef struct deque* Deque;

// Function to create a new deque
Deque createDeque() {
	Deque newDeque = malloc(sizeof(struct deque));  // Allocate memory for the new deque
	newDeque->head = NULL;                           // Initialize head pointer to NULL
	newDeque->tail = NULL;                           // Initialize tail pointer to NULL
	newDeque->elements = 0;                          // Initialize number of elements to 0
	return newDeque;                                 // Return the new deque
}

int dequeIsEmpty(Deque deque) {
	if (deque == NULL) return -1;   // Check if deque is NULL
	return deque->elements == 0;    // Return 1 if deque is empty, 0 otherwise
}

int dequeSize(Deque deque) {
	if (deque == NULL) return -1;    // Check if deque is NULL
	return deque->elements;          // Return the number of elements in the deque
}

void dequePush(Deque deque, int data) {
	if (deque == NULL) return;  // Check if deque is NULL

	NodePtr newNode = createNode(data);  // Create a new node with the given data
	newNode->next = deque->head;         // Set the next pointer of the new node to the current head

	if (deque->head == NULL) deque->tail = newNode;  // If deque is empty, set tail to the new node
	else deque->head->prev = newNode;                // Otherwise, set previous pointer of current head to the new node

	deque->head = newNode;    // Set the head of the deque to the new node
	deque->elements++;        // Increment the number of elements in the deque
}

void dequeEnque(Deque deque, int data) {
	if (deque == NULL) return;  // Check if deque is NULL

	NodePtr newNode = createNode(data);  // Create a new node with the given data
	newNode->prev = deque->tail;         // Set the previous pointer of the new node to the current tail

	if (deque->tail == NULL) deque->head = newNode;  // If deque is empty, set head to the new node
	else deque->tail->next = newNode;                // Otherwise, set next pointer of current tail to the new node

	deque->tail = newNode;    // Set the tail of the deque to the new node
	deque->elements++;        // Increment the number of elements in the deque
}

int dequePop(Deque deque) {
	if (dequeIsEmpty(deque)) return -1;  // Check if deque is empty, return -1 if true

	NodePtr node = deque->head;         // Get the node at the front of the deque
	deque->head = deque->head->next;    // Update the head of the deque

	if (deque->head == NULL) deque->tail = NULL;  // If deque becomes empty, set tail to NULL
	else deque->head->prev = NULL;                 // Otherwise, set previous pointer of new head to NULL

	deque->elements--;    // Decrement the number of elements in the deque

	int data = node->data;  // Get the data from the node
	free(node);             // Free memory allocated for the node
	return data;            // Return the data
}

int dequeDequeue(Deque deque) {
	if (dequeIsEmpty(deque)) return -1;  // Check if deque is empty, return -1 if true

	NodePtr node = deque->tail;         // Get the node at the back of the deque
	deque->tail = deque->tail->prev;    // Update the tail of the deque

	if (deque->tail == NULL) deque->head = NULL;  // If deque becomes empty, set head to NULL
	else deque->tail->next = NULL;                 // Otherwise, set next pointer of new tail to NULL

	deque->elements--;    // Decrement the number of elements in the deque

	int data = node->data;  // Get the data from the node
	free(node);             // Free memory allocated for the node
	return data;            // Return the data
}

void dequePrint(Deque deque) {
	if (deque == NULL) return;    // Check if deque is NULL

	NodePtr cursor;               // Cursor to iterate through the deque
	for (cursor = deque->head; cursor != NULL; cursor=cursor->next) {
		printf("%d ", cursor->data);  // Print the data of each node
	}
	putchar('\n');  // Print a new line after printing all elements
}
