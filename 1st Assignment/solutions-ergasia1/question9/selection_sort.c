#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void selectionSort(int* data, int size) {
	for (int i = 0; i < size; i++) { // Loop through the array
		int min = data[i], minIndex = i; // Initialize minimum value and its index

		for (int j = i + 1; j < size; j ++) { // Find the minimum element in the unsorted part of the array
			if (data[j] < min) { // If a smaller element is found
				min = data[j]; // Update the minimum value
				minIndex = j; // Update the index of the minimum value
			}
		}

		// Swap the current element with the minimum element
		int temp = data[i];
		data[i] = data[minIndex];
		data[minIndex] = temp;
	}
}

void listSelectionSort(List list) {
	NodePtr cursor1; // Cursor to iterate through the list
	for (cursor1 = list; cursor1->next != NULL; cursor1 = cursor1->next) { // Loop through the list
		int min = cursor1->data; // Initialize minimum value
		NodePtr cursor2, minCursor; // Cursors for comparing elements and storing the minimum element

		for (cursor2 = cursor1->next; cursor2 != NULL; cursor2 = cursor2->next) { // Find the minimum element in the unsorted part of the list
			if (cursor2->data < min) { // If a smaller element is found
				min = cursor2->data; // Update the minimum value
				minCursor = cursor2; // Update the cursor pointing to the minimum element
			}
		}

		// Swap the data of the current node with the minimum element
		int temp = cursor1->data;
		cursor1->data = minCursor->data;
		minCursor->data = temp;
	}
}

void printArray(int* a, int size) {
	for (int i = 0; i < size; i++) { // Loop through the array
		printf("%d ", a[i]); // Print each element followed by a space
	}
	putchar('\n'); // Move to the next line after printing all elements
}
