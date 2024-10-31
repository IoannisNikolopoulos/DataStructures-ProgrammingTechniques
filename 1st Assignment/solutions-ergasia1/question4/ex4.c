#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main() {
    Deque deque = createDeque();
    int choice = 0, data;
    do {
        printf("1. Push\n");
        printf("2. Enqueue\n");
        printf("3. Pop\n");
        printf("4. Dequeue\n");
        printf("5. Print\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                dequePush(deque, data);
                break;
            case 2:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                dequeEnque(deque, data);
                break;
            case 3:
                data = dequePop(deque);
                if (data != -1)
                    printf("Popped element: %d\n", data);
                else
                    printf("Deque is empty!\n");
                break;
            case 4:
                data = dequeDequeue(deque);
                if (data != -1)
                    printf("Dequeued element: %d\n", data);
                else
                    printf("Deque is empty!\n");
                break;
            case 5:
                dequePrint(deque);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}