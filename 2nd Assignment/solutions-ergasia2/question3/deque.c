#include <stdio.h>
#include <stdlib.h>

// Typedef for a pointer to a BST node, assuming it's defined elsewhere
typedef struct BSTnode* Data;

// Definition of a doubly-linked list node structure
struct node {
	Data data;           // Data stored in the node, in this case, a BST node pointer
	struct node *next;   // Pointer to the next node in the list
	struct node *prev;   // Pointer to the previous node in the list
};

// Typedefs for convenience
typedef struct node Node;
typedef Node* NodePtr;
typedef NodePtr List;

// Function to create a new node with the given data
NodePtr createNode(Data incomingData) {
	NodePtr newNode = malloc(sizeof(Node)); // Allocate memory for the new node
	newNode->data = incomingData;           // Set the node's data
	newNode->next = NULL;                   // Initialize next pointer to NULL
	newNode->prev = NULL;                   // Initialize prev pointer to NULL
	return newNode;                         // Return the new node
}

// Definition of a deque structure
struct deque {
	NodePtr head;        // Pointer to the first node in the deque
	NodePtr tail;        // Pointer to the last node in the deque
	int elements;        // Count of elements in the deque
};

// Typedef for convenience
typedef struct deque* Deque;

// Function to create a new deque
Deque createDeque() {
	Deque newDeque = malloc(sizeof(struct deque)); // Allocate memory for the deque
	newDeque->head = NULL;                         // Initialize head pointer to NULL
	newDeque->tail = NULL;                         // Initialize tail pointer to NULL
	newDeque->elements = 0;                        // Initialize element count to 0
	return newDeque;                               // Return the new deque
}

// Function to check if the deque is empty
int dequeIsEmpty(Deque deque) {
	if (deque == NULL) return -1;                  // Return -1 if the deque is NULL
	return deque->elements == 0;                   // Return 1 if empty, 0 otherwise
}

// Function to get the size of the deque
int dequeSize(Deque deque) {
	if (deque == NULL) return -1;                  // Return -1 if the deque is NULL
	return deque->elements;                        // Return the number of elements
}

// Function to push data onto the front of the deque
void dequePush(Deque deque, Data data) {
	if (deque == NULL) return;                     // Do nothing if the deque is NULL

	NodePtr newNode = createNode(data);            // Create a new node with the data
	newNode->next = deque->head;                   // Set the new node's next to current head

	if (deque->head == NULL) deque->tail = newNode; // If the deque was empty, set tail to new node
	else deque->head->prev = newNode;              // Otherwise, set current head's prev to new node

	deque->head = newNode;                         // Set head to new node
	deque->elements++;                             // Increment element count
}

// Function to enqueue data onto the back of the deque
void dequeEnque(Deque deque, Data data) {
	if (deque == NULL) return;                     // Do nothing if the deque is NULL

	NodePtr newNode = createNode(data);            // Create a new node with the data
	newNode->prev = deque->tail;                   // Set the new node's prev to current tail

	if (deque->tail == NULL) deque->head = newNode; // If the deque was empty, set head to new node
	else deque->tail->next = newNode;              // Otherwise, set current tail's next to new node

	deque->tail = newNode;                         // Set tail to new node
	deque->elements++;                             // Increment element count
}

// Function to pop data from the front of the deque
Data dequePop(Deque deque) {
	if (dequeIsEmpty(deque)) return NULL;          // Return NULL if the deque is empty

	NodePtr node = deque->head;                    // Get the current head node
	deque->head = deque->head->next;               // Move head to the next node

	if (deque->head == NULL) deque->tail = NULL;   // If the deque is now empty, set tail to NULL
	else deque->head->prev = NULL;                 // Otherwise, set new head's prev to NULL

	deque->elements--;                             // Decrement element count

	Data data = node->data;                        // Get the data from the node
	free(node);                                    // Free the node
	return data;                                   // Return the data
}

// Function to dequeue data from the back of the deque
Data dequeDequeue(Deque deque) {
	if (dequeIsEmpty(deque)) return NULL;          // Return NULL if the deque is empty

	NodePtr node = deque->tail;                    // Get the current tail node
	deque->tail = deque->tail->prev;               // Move tail to the previous node

	if (deque->tail == NULL) deque->head = NULL;   // If the deque is now empty, set head to NULL
	else deque->tail->next = NULL;                 // Otherwise, set new tail's next to NULL

	deque->elements--;                             // Decrement element count

	Data data = node->data;                        // Get the data from the node
	free(node);                                    // Free the node
	return data;                                   // Return the data
}

