#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

struct node {
	int data;
	struct node *next;
};

typedef struct node *NodePtr;
typedef NodePtr List;

void selectionSort(int* data, int size);
void listSelectionSort(List list);
void printArray(int* a, int size);

#endif //SELECTION_SORT_H