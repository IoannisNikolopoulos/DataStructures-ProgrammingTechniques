#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main() {
    PriorityQueue pq = PQCreate();
    int choice, data;

    do {
        printf("\nPriority Queue Operations\n");
        printf("1. Insert\n");
        printf("2. Remove\n");
        printf("3. Size\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                PQInsert(pq, data);
                break;
            case 2:
                if (PQEmpty(pq))
                    printf("Priority Queue is empty.\n");
                else
                    printf("Removed element: %d\n", PQRemove(pq));
                break;
            case 3:
                printf("Size of Priority Queue: %d\n", PQSize(pq));
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
