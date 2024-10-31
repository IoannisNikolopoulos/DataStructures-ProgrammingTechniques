#include <stdlib.h>

typedef int Item;
#define NULLItem 0

// Definition of the priority queue structure
typedef struct priority_queue {
    int Count;       // Number of items in the queue
    Item *ItemArray; // Array to store items
} PriorityQueue;

typedef PriorityQueue* PQPointer;

// Function to initialize a priority queue
PQPointer QUEUEinit(int maxN) {
    PQPointer newPq = malloc(sizeof(PriorityQueue));        // Allocate memory for the priority queue
    newPq->Count = maxN;                                    // Set the initial count to maxN
    newPq->ItemArray = calloc(maxN, sizeof(Item));          // Allocate and initialize the item array
    return newPq;                                           // Return the initialized priority queue
}

// Function to check if the priority queue is empty
int QUEUEempty(PQPointer pq) {
    return pq->ItemArray[1] == NULLItem;                    // Check if the first item is NULLItem (indicating empty queue)
}

// Function to insert an item into the priority queue
void QUEUEput(PQPointer pq, Item item) {
    int index = 0;
    for (int i = 1; i < pq->Count; i++) {                   // Find the first empty spot in the item array
        if (pq->ItemArray[i] == NULLItem) {
            index = i;                                      // Store the index of the empty spot
            pq->ItemArray[i] = item;                        // Insert the new item
            break;
        }
    }

    if (index == 0) {                                       // If no empty spot is found
        index = pq->Count;                                  // Use the last position
        pq->Count *= 2;                                     // Double the size of the queue
        pq->ItemArray = realloc(pq->ItemArray, pq->Count * sizeof(Item)); // Reallocate memory for the item array
        pq->ItemArray[index] = item;                        // Insert the new item
    }

    // Reheapify to maintain the heap property
    while (index != 1 && pq->ItemArray[index] > pq->ItemArray[index/2]) {
        Item temp = pq->ItemArray[index/2];                 // Swap the new item with its parent if it's larger
        pq->ItemArray[index/2] = pq->ItemArray[index];
        pq->ItemArray[index] = temp;

        index = index/2;                                    // Move up the tree
    }
}

// Function to remove and return the maximum item from the priority queue
Item QUEUEget(PQPointer pq) {
    if (QUEUEempty(pq) == 1) return NULLItem;               // If the queue is empty, return NULLItem

    Item temp = pq->ItemArray[1];                           // Store the maximum item
    pq->ItemArray[1] = NULLItem;                            // Remove the maximum item

    int index = 1;                                          // Start from the root
    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;
    do {
        // Compare left and right children and swap with the larger one
        if (pq->ItemArray[leftChild] > pq->ItemArray[rightChild]) {
            Item t = pq->ItemArray[leftChild];
            pq->ItemArray[leftChild] = pq->ItemArray[index];
            pq->ItemArray[index] = t;
            index = leftChild;
        } else {
            Item t = pq->ItemArray[rightChild];
            pq->ItemArray[rightChild] = pq->ItemArray[index];
            pq->ItemArray[index] = t;
            index = rightChild;
        }
        leftChild = 2 * index;
        rightChild = 2 * index + 1;
    } while (leftChild < pq->Count && rightChild < pq->Count &&
             pq->ItemArray[leftChild] != NULLItem && pq->ItemArray[rightChild] != NULLItem);

    return temp;                                            // Return the removed item
}
