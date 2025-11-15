#include "queueImplementation.h"
#include <stdio.h>
#include"validators.h"
#include<stdlib.h>

int getQueueCount() {
    printf("Enter number of queues (3-5): ");
    return getValidInput(3, 5);
}

int areQueuesEqual(Queue *q1, Queue *q2) {
    if (q1->size != q2->size) return 0;

    Node *n1 = q1->top, *n2 = q2->top;
    while (n1 && n2) {
        if (n1->value != n2->value) return 0;
        n1 = n1->next;
        n2 = n2->next;
    }
    return 1;
}

void printQueueWithIndex(Queue *queue, int index) {
    printf("Queue %d: [", index);
    Node *current = queue->top;
    while (current) {
        printf("%d", current->value);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

void checkForDuplicateQueues(Queue **queues, int numQueues) {
    int found = 0;
    for (int i = 0; i < numQueues; i++) {
        for (int j = i + 1; j < numQueues; j++) {
            if (areQueuesEqual(queues[i], queues[j])) {
                printf("\n-----------------------------\n");
                printf("Queues %d and %d are identical:\n", i + 1, j + 1);
                printQueueWithIndex(queues[i], i + 1);
                printQueueWithIndex(queues[j], j + 1);
                printf("-----------------------------\n");
                found = 1;
            }
        }
    }
    if (!found) {
        printf("\n-----------------------------\n");
        printf("No identical queues found!\n");
        printf("-----------------------------\n");
    }
}


void findSameQueue() {
    printf("\n-----------------------------\n");
    printf("Enter number of queues (3-5): ");
    int queueCount = getValidInput(3, 5);
    Queue **queues = malloc(queueCount * sizeof(Queue*));

    printf("\n-----------------------------\n");
    for (int i = 0; i < queueCount; i++) {
        printf("Queue %d\n", i + 1);
        printf("Enter size (4 or 5): ");
        int size = getValidInput(4, 5);
        queues[i] = fillQueue(size);
        printf("Queue %d created with %d elements\n", i+1, size);
    }

    printf("\n-----------------------------\n");
    printf("Checking for identical queues...\n");
    checkForDuplicateQueues(queues, queueCount);

    for (int i = 0; i < queueCount; i++) {
        freeQueue(queues[i]);
    }
    free(queues);
}


