#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h" 
#include "selection_sort.h"

int main() {
	int A[] = {4, 3, 5, 1, 6, 2};

	List list = createList();

	for (int i = 0; i < sizeof(A)/sizeof(*A); i++) { // Loop through the array (sizeof(A)/sizeof(*A) evaluates to the number of elements in the array)
		enqueueNode(&list, createNode(A[i])); // Enqueue each element into the linked list
	}

	// Print the original array
	printArray(A, sizeof(A)/sizeof(*A));
	// Sort the array using selection sort
	selectionSort(A, sizeof(A)/sizeof(*A));
	// Print the sorted array
	printArray(A, sizeof(A)/sizeof(*A));

	// Print the original linked list
	printList(list);
	// Sort the linked list using selection sort
	listSelectionSort(list);
	// Print the sorted linked list
	printList(list);

	return 0;
}

