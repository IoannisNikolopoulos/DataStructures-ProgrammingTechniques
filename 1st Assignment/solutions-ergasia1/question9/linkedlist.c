#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;            // Data stored in the node
	struct node *next;  // Pointer to the next node
};

typedef struct node Node;
typedef Node* NodePtr;
typedef NodePtr List;  // Alias for NodePtr to represent a list

NodePtr createNode(int incomingData) {
	NodePtr newNode = malloc(sizeof(Node));  // Allocate memory for the new node
	newNode->data = incomingData;            // Set the data of the new node
	newNode->next = NULL;                     // Initialize next pointer to NULL
	return newNode;                           // Return the new node
}

int listSize(List list) {
	int size = 0;            // Initialize size to 0
	NodePtr cursor;          // Cursor to iterate through the list
	for (cursor = list; cursor != NULL; cursor = cursor->next, size++);  // Loop through the list and count the nodes
	return size;             // Return the size of the list
}

int listIsEmpty(List list) {
	return list == NULL;  // Return 1 if the list is empty, 0 otherwise
}

void pushNode(List* list, NodePtr node) {
	if (list == NULL) return;  // Check if the list pointer is NULL

	node->next = *list;  // Set the next pointer of the new node to the current head of the list
	*list = node;        // Update the head pointer of the list to the new node
}

List createList() {
	return NULL;  // Return NULL to represent an empty list
}

void enqueueNode(List* list, NodePtr node) {
	if (list == NULL) return;  // Check if the list pointer is NULL

	if (*list == NULL) {  // If the list is empty
		*list = node;     // Set the head of the list to the new node
		return;
	}

	NodePtr cursor;  // Cursor to iterate through the list
	for (cursor = *list; cursor->next != NULL; cursor = cursor->next);  // Move cursor to the last node in the list

	cursor->next = node;  // Set the next pointer of the last node to the new node
}

void insertNode(List* list, NodePtr node, int index) {
	if (list == NULL) return;  // Check if the list pointer is NULL

	if (*list == NULL) {  // If the list is empty
		*list = node;     // Set the head of the list to the new node
		return;
	}

	if (index == 0) {  // If the index is 0 (insertion at the beginning of the list)
		node->next = *list;  // Set the next pointer of the new node to the current head of the list
		*list = node;        // Update the head pointer of the list to the new node
		return;
	}

	NodePtr cursor = *list;  // Cursor to iterate through the list
	for (int i = 0; i < index && cursor->next != NULL; cursor = cursor->next, i++);  // Move cursor to the node at the specified index

	NodePtr temp = cursor->next;  // Store the next node temporarily
	node->next = temp;             // Set the next pointer of the new node to the next node
	cursor->next = node;           // Set the next pointer of the current node to the new node
}

NodePtr dequeueNode(List* list) {
	if (list == NULL || *list == NULL) return NULL;  // If the list pointer or head pointer is NULL, return NULL

	if ((*list)->next == NULL) {  // If there's only one node in the list
		NodePtr temp = *list;     // Store the head node temporarily
		*list = NULL;             // Update the head pointer of the list to NULL
		return temp;              // Return the stored head node
	}

	NodePtr cursor;             // Cursor to iterate through the list
	for (cursor = *list; cursor->next->next != NULL; cursor = cursor->next);  // Move cursor to the second-to-last node in the list

	NodePtr temp = cursor->next;  // Store the last node temporarily
	cursor->next = NULL;           // Set the next pointer of the second-to-last node to NULL
	return temp;                   // Return the stored last node
}

NodePtr popNode(List* list) {
	if (list == NULL || *list == NULL) return NULL;  // If the list pointer or head pointer is NULL, return NULL

	NodePtr temp = *list;  // Store the head node temporarily
	*list = (*list)->next;  // Update the head pointer of the list to the next node
	return temp;            // Return the stored head node
}

void printList(List list) {
	NodePtr cursor;  // Cursor to iterate through the list
	for (cursor = list; cursor != NULL; cursor = cursor->next) {  // Loop through the list
		printf("%d ", cursor->data);  // Print the data of each node followed by a space
	}
	putchar('\n');  // Move to the next line after printing all elements
}
