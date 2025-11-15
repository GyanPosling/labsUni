#include "queueTask.h"
#include <stdio.h>
#include <stdlib.h>

#include "validators.h"

int findFirstNegative(Queue *queue) {
    int index = 0;
    if (isEmpty(queue))
        return -1;

    Node *current = queue->top;
    while (current != NULL) {
        if (current->value < 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

Queue* getNecessaryQueue(Queue* queue) {
    Queue* newQueue = initQueue();
    Node* current = queue->top;
    int negativeFound = 0;

    while (current != NULL) {
        if (!negativeFound) {
            push(newQueue, current->value);
            if (current->value < 0) {
                negativeFound = 1;
            }
        }
        current = current->next;
    }

    if (!negativeFound) {
        freeQueue(newQueue);
        return queue;
    }

    return newQueue;
}


int getSize(Queue *queue) {
    return queue->size;
}

void runQueue() {
    printf("\nEnter queue size (1-100): ");
    int size = getValidInput(6, 6);

    Queue* startQueue = fillQueueInteractive(size);
    Queue* necessaryQueue = getNecessaryQueue(startQueue);

    printf("\n-----------------------------\n");
    printf("Original queue:\n");
    showQueue(startQueue);

    printf("\n-----------------------------\n");
    printf("Processing result:\n");
    if (necessaryQueue == startQueue) {
        printf("No negative elements found. Full queue:\n");
    }
    showQueue(necessaryQueue);
    printf("\nRemaining size: %d\n", getSize(necessaryQueue));
    printf("-----------------------------\n");

    if (necessaryQueue != startQueue) {
        freeQueue(startQueue);
        freeQueue(necessaryQueue);
    } else {
        freeQueue(startQueue);
    }
}
