#include "dequeImplementation.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"

Deque *initDeque() {
    Deque *deque = malloc(sizeof(Deque));
    deque->front = NULL;
    deque->back = NULL;
    deque->size = 0;
    return deque;
}

int isEmptyDeque(Deque *deque) {
    return deque->size == 0;
}

void pushFront(Deque *deque, int value) {
    DequeNode *node = malloc(sizeof(DequeNode));
    node->value = value;
    node->next = deque->front;
    node->prev = NULL;

    if (isEmptyDeque(deque)) {
        deque->front = node;
        deque->back = node;
    } else {
        deque->front->prev = node;
        deque->front = node;
    }
    deque->size++;
}

void pushBack(Deque *deque, int value) {
    DequeNode *node = malloc(sizeof(DequeNode));
    node->value = value;
    node->prev = deque->back;
    node->next = NULL;

    if (isEmptyDeque(deque)) {
        deque->front = node;
        deque->back = node;
    } else {
        deque->back->next = node;
        deque->back = node;
    }
    deque->size++;
}

int popFront(Deque *deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1;
    }

    DequeNode *node = deque->front;
    int value = node->value;

    deque->front = node->next;
    if (deque->front) {
        deque->front->prev = NULL;
    } else {
        deque->back = NULL;
    }

    free(node);
    deque->size--;
    return value;
}

int popBack(Deque *deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1;
    }

    DequeNode *node = deque->back;
    int value = node->value;

    deque->back = node->prev;
    if (deque->back) {
        deque->back->next = NULL;
    } else {
        deque->front = NULL;
    }

    free(node);
    deque->size--;
    return value;
}

int peekFront(Deque *deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->front->value;
}

int peekBack(Deque *deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->back->value;
}

Deque* fillDequeInteractive(int maxSize) {
    Deque* deque = initDeque();
    char input[100];

    printf("Enter up to %d numbers (press Enter without number to finish):\n", maxSize);

    while (deque->size < maxSize) {
        printf("Element %d: ", deque->size + 1);

        if (!fgets(input, sizeof(input), stdin)) break;

        if (isInputEmpty(input)) break;

        int value;
        if (sscanf(input, "%d", &value) == 1) {
            pushBack(deque, value);
        } else {
            printf("Invalid input. Please enter a number or just press Enter to finish\n");
        }
    }

    return deque;
}

void showDeque(Deque *deque) {
    if (isEmptyDeque(deque)) {
        printf("Deque is empty\n");
        return;
    }

    DequeNode *current = deque->front;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeDeque(Deque *deque) {
    DequeNode *current = deque->front;
    while (current) {
        DequeNode *next = current->next;
        free(current);
        current = next;
    }
    free(deque);
}

