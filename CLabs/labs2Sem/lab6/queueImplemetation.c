#include "queueImplementation.h"
#include <stdio.h>
#include <stdlib.h>

#include "validators.h"

Queue *initQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->top = NULL;
    queue->bottom = NULL;
    queue->size = 0;
    return queue;
}

int isEmpty(Queue *queue) {
    return queue->size == 0;
}

void push(Queue *queue, int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if (isEmpty(queue)) {
        queue->top = node;
        queue->bottom = node;
    } else {
        node->prev = queue->bottom;
        queue->bottom->next = node;
        queue->bottom = node;
    }
    queue->size++;
}

int pop(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    Node *node = queue->top;
    int value = node->value;

    queue->top = node->next;
    if (queue->top) {
        queue->top->prev = NULL;
    } else {
        queue->bottom = NULL;
    }

    free(node);
    queue->size--;
    return value;
}

int peek(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->top->value;
}

int peekLast(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->bottom->value;
}


Queue* fillQueueInteractive(int maxSize) {
    Queue* queue = initQueue();
    char input[100];

    printf("Enter up to %d numbers (press Enter to finish):\n", maxSize);

    while (queue->size < maxSize) {
        printf("Element %d: ", queue->size + 1);

        if (!fgets(input, sizeof(input), stdin)) break;

        if (isInputEmpty(input)) break;

        int value;
        if (sscanf(input, "%d", &value) == 1) {
            push(queue, value);
        } else {
            printf("Invalid input. Enter a number or press Enter\n");
        }
    }

    return queue;
}

Queue *fillQueue(int size) {
    Queue *queue = initQueue();
    int i = 0;
    while (queue->size < size) {
        printf("Enter %d value of queue: ", i+1);
        push(queue, getValidInput(-100, 100));
        i++;
    }
    return queue;
}

void showQueue(Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    Node *current = queue->top;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(Queue *queue) {
    Node *current = queue->top;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}