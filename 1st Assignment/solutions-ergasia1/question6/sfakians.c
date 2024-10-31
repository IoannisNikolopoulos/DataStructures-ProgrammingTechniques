#include <stdio.h>
#include <stdlib.h>
#include "circularList.h" // Include the header file for the circular linked list implementation

int main(int argc, char* argv[]){
    if (argc < 4){  // Check if there are enough command line arguments
        printf ("Not enough arguments.\n"); // Print error message
        return -1;  // Return -1 to indicate error
    }
    int N = atoi(argv[1]);  // Convert the first argument to an integer (N)
    int M = atoi(argv[2]);  // Convert the second argument to an integer (M)
    int P = atoi(argv[3]);  // Convert the third argument to an integer (P)
    if (N < 1 || M < 1 || P < 0 || P > (N-1)){  // Check if the arguments are valid
        printf("Invalid argument value.\n");  // Print error message
        return -2;  // Return -2 to indicate error
    }
    CircularList circle = createCircularList();  // Create an empty circular linked list
    for (int i = N-1; i >= 0; i--){  // Loop to add N elements to the list
        circle = circularListAdd(circle, i);  // Add each element to the list
    }
    circle = advanceCursor(circle);  // Move the cursor to the next node
    for (int i = 0; i < P; i++){  // Loop to move the cursor P times
        circle = advanceCursor(circle);  // Move the cursor to the next node
    }
    for (int i = 0; i < N; i++){  // Loop to eliminate N persons from the list
        for (int j = 0; j < M-1; j++){  // Loop to move the cursor M-1 times
            circle = advanceCursor(circle);  // Move the cursor to the next node
        }
        int pos = circularListRemove(&circle);  // Remove the person at the cursor position
        printf ("Person %d was eliminated.\n", pos);  // Print the eliminated person's position
    }
    return 0;  // Return 0 to indicate successful execution
}
