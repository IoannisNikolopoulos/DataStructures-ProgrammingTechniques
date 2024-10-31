#include <stdio.h>
#include <stdlib.h>

// Definition of the node structure
struct node {
    int data;            // Data stored in the node
    struct node* next;   // Pointer to the next node in the list
    struct node* prev;   // Pointer to the previous node in the list
};

typedef struct node Node;     // Typedef for struct node
typedef Node* NodePtr;        // Typedef for struct node*

// Function to create a new node with the given data
NodePtr createNode(int data) {
    NodePtr newNode = malloc(sizeof(struct node));   // Allocate memory for the new node
    newNode->data = data;                             // Set the data of the new node
    newNode->next = NULL;                             // Initialize the next pointer to NULL
    return newNode;                                   // Return the new node
}

void main() {
    // Create five nodes with different data values
    NodePtr firstNode = createNode(5);
    NodePtr secondNode = createNode(2);
    NodePtr thirdNode = createNode(7);
    NodePtr fourthNode = createNode(3);
    NodePtr fifthNode = createNode(8);

    // Array to store the node pointers
    NodePtr myNodeArr[] = {firstNode, secondNode, thirdNode, fourthNode, fifthNode};

    int i = 0;
    int arrSize = sizeof(myNodeArr) / sizeof(myNodeArr[i]);  // Calculate the size of the array

    // Turn nodes into a linked list
    for (NodePtr currentNode = myNodeArr[i]; i < arrSize - 1; i++) {
        currentNode = myNodeArr[i];   // Get the current node
        currentNode->next = myNodeArr[i+1];  // Set the next pointer of the current node
    }

    // Print the next pointer of the last node in the array
    printf("%p\n", fifthNode->next);

    // Print the linked list
    i = 0;
    for (NodePtr cursor = firstNode; i < arrSize; cursor = cursor->next, i++) {
        // printf("%d\n", cursor->data);
    }

    printf("\n");

    // Reverse the linked list
    NodePtr cursor;
    NodePtr temp = firstNode;
    firstNode->prev = firstNode->next;
    firstNode->next = NULL;

    i = 0;
    for (cursor = secondNode; i < arrSize - 1; cursor = cursor->prev, i++) {
        cursor->prev = cursor->next;
        cursor->next = temp;
        temp = cursor;
    }

    // Print the reversed linked list
    i = 0;
    for (NodePtr cursor = fifthNode; i < arrSize; cursor = cursor->next, i++) {
        printf("%d ", cursor->data);
        printf("%p\n", cursor->prev);
    }

    return;
}
