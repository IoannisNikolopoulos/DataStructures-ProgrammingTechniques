#include <stdio.h>
#include <stdlib.h>
#include "circularList.h"

int main() {
    CircularList cursor = NULL;
    int choice, data;

    do {
        printf("1. Add element\n");
        printf("2. Remove element\n");
        printf("3. Advance cursor\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to add: ");
                scanf("%d", &data);
                cursor = circularListAdd(cursor, data);
                break;
            case 2:
                data = circularListRemove(&cursor);
                if (data != 0)
                    printf("Removed element: %d\n", data);
                else
                    printf("List is empty!\n");
                break;
            case 3:
                if (cursor != NULL) {
                    cursor = advanceCursor(cursor);
                    printf("Cursor advanced.\n");
                } else {
                    printf("List is empty!\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                return -1;
        }
    } while (choice != 4);
    
    return 0;
}
