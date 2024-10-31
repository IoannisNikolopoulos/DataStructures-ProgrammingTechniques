#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;            // Data stored in the node
    struct node *next;   // Pointer to the next node
};

typedef struct node Node;
typedef Node* NodePtr;

NodePtr createNode(int data) {
    NodePtr newNode = malloc(sizeof(Node));  // Allocate memory for the new node
    newNode->data = data;                    // Set the data of the new node
    newNode->next = NULL;                    // Initialize next pointer to NULL
    return newNode;                          // Return the new node
}

NodePtr createCircularList() {
    NodePtr cursor = NULL;  // Initialize cursor to NULL
    return cursor;          // Return the cursor
}

NodePtr circularListAdd(NodePtr cursor, int data) {
    NodePtr newNode = createNode(data);  // Create a new node with the given data
    if (cursor == NULL){  // If the cursor is NULL, indicating an empty list
        cursor = newNode;  // Set cursor to the new node
        cursor->next = cursor;  // Make the new node point to itself
    }
    else{  // If the list is not empty
        newNode->next = cursor->next;  // Set the next pointer of the new node
        cursor->next = newNode;        // Make the current node point to the new node
    }
    return cursor;  // Return the cursor
}

int circularListRemove(NodePtr *cursor) {
    if (*cursor == NULL){  // If the cursor is NULL, indicating an empty list
        return 0;  // Return 0 indicating no removal
    }
    if ((*cursor)->next == *cursor){  // If there's only one node in the list
        int data = (*cursor)->data;    // Get the data of the node
        free(*cursor);                 // Free memory allocated for the node
        *cursor = NULL;                // Set cursor to NULL
        return data;                   // Return the data
    }
    int data = (*cursor)->next->data;  // Get the data of the next node
    NodePtr temp = (*cursor)->next;    // Store the next node temporarily
    (*cursor)->next = (*cursor)->next->next;  // Remove the next node from the list
    free(temp);                        // Free memory allocated for the removed node
    return data;                       // Return the data
}

NodePtr advanceCursor(NodePtr cursor) {
    cursor = cursor->next;  // Move the cursor to the next node
    return cursor;          // Return the updated cursor
}
