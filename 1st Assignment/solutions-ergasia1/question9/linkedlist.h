#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node {
	int data;
	struct node *next;
};

typedef struct node *NodePtr;
typedef NodePtr List;

NodePtr createNode(int incomingData);
int listSize(List list);
int listIsEmpty(List list);
void pushNode(List* list, NodePtr node);
List createList();
void enqueueNode(List* list, NodePtr node);
void insertNode(List* list, NodePtr node, int index);
NodePtr dequeueNode(List* list);
NodePtr popNode(List* list);
void printList(List list);

#endif //LINKEDLIST_H
