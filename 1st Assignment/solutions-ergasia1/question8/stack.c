#include <stdlib.h>

struct node {
	char* data;          // Data stored in the node (a pointer to char)
	struct node* next;  // Pointer to the next node
};

typedef struct node* NodePtr;

struct stack {
	NodePtr head;  // Pointer to the top of the stack
	int elements;  // Number of elements in the stack
};

typedef struct stack* Stack;

Stack createStack() {
	Stack stack = malloc(sizeof(*stack));  // Allocate memory for the stack
	stack->head = NULL;                     // Initialize head pointer to NULL
	stack->elements = 0;                    // Initialize number of elements to 0
	return stack;                           // Return the new stack
}

void stackPush(Stack stack, char* c) {
	NodePtr node = malloc(sizeof(*node));  // Allocate memory for a new node
	node->data = c;                        // Set the data of the new node
	node->next = stack->head;              // Point the new node to the current top of the stack
	stack->head = node;                    // Update the top of the stack to the new node
	stack->elements++;                     // Increment the number of elements in the stack
}

char* stackPop(Stack stack) {
	if (stack->head == NULL) return NULL;  // If stack is empty, return NULL

	NodePtr head = stack->head;            // Get the top node of the stack
	stack->head = stack->head->next;       // Move the top pointer to the next node
	char* c = head->data;                  // Get the data from the top node
	free(head);                            // Free memory allocated for the top node
	return c;                              // Return the data
}
