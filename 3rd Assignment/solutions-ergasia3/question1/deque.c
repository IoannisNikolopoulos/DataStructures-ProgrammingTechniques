#include <stdio.h>
#include <stdlib.h>

typedef struct BSTnode* Data;

struct node {
	Data data;
	struct node *next;
	struct node *prev;
};

typedef struct node Node;
typedef Node* NodePtr;
typedef NodePtr List;

NodePtr createNode(Data incomingData) {
	NodePtr newNode = malloc(sizeof(Node));
	newNode->data = incomingData;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

struct deque {
	NodePtr head;
	NodePtr tail;
	int elements;
};

typedef struct deque* Deque;

Deque createDeque() {
	Deque newDeque = malloc(sizeof(struct deque));
	newDeque->head = NULL;
	newDeque->tail = NULL;
	newDeque->elements = 0;
	return newDeque;
}

int dequeIsEmpty(Deque deque) {
	if (deque == NULL) return -1;
	return deque->elements == 0;
}

int dequeSize(Deque deque) {
	if (deque == NULL) return -1;
	return deque->elements;
}

void dequePush(Deque deque, Data data) {
	if (deque == NULL) return;

	NodePtr newNode = createNode(data);
	newNode->next = deque->head;

	if (deque->head == NULL) deque->tail = newNode;
	else deque->head->prev = newNode;

	deque->head = newNode;

	deque->elements++;
}

void dequeEnque(Deque deque, Data data) {
	if (deque == NULL) return;

	NodePtr newNode = createNode(data);
	newNode->prev = deque->tail;

	if (deque->tail == NULL) deque->head = newNode;
	else deque->tail->next = newNode;

	deque->tail = newNode;

	deque->elements++;
}

Data dequePop(Deque deque) {
	if (dequeIsEmpty(deque)) return NULL;

	NodePtr node = deque->head;
	deque->head = deque->head->next;

	if (deque->head == NULL) deque->tail = NULL;
	else deque->head->prev = NULL;

	deque->elements--;

	Data data = node->data;
	free(node);
	return data;
}

Data dequeDequeue(Deque deque) {
	if (dequeIsEmpty(deque)) return NULL;

	NodePtr node = deque->tail;
	deque->tail = deque->tail->prev;

	if (deque->tail == NULL) deque->head = NULL;
	else deque->tail->next = NULL;

	deque->elements--;

	Data data = node->data;
	free(node);
	return data;
}

void dequeDelete(Deque deque) {
	while (!dequeIsEmpty(deque)) {
		dequePop(deque);
	}
	free(deque);
}
