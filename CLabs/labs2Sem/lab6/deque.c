#include "deque.h"
#include "dequeImplementation.h"
#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getDequeSize(Deque *deque) {
    return deque->size;
}

Deque* getFirstThreeAndLastThreeElements(Deque *deque) {
    Deque* result = initDeque();
    if (getDequeSize(deque) < 6) return result;

    DequeNode* current = deque->front;
    for (int i = 0; i < 3; i++) {
        pushBack(result, current->value);
        current = current->next;
    }

    current = deque->back;
    for (int i = 0; i < 3; i++) {
        pushFront(result, current->value);
        current = current->prev;
    }

    return result;
}

int findFirstNegativeFromRight(Deque *deque) {
    DequeNode* current = deque->back;
    while (current) {
        if (current->value < 0) return current->value;
        current = current->prev;
    }
    return 0;
}

Deque* getElementsUntilFirstNegativeFromRight(Deque *deque) {
    Deque* result = initDeque();
    Deque* temp = initDeque();

    while (!isEmptyDeque(deque)) {
        int val = popBack(deque);
        pushFront(temp, val);
        if (val < 0) break;
    }

    while (!isEmptyDeque(temp)) {
        pushBack(result, popFront(temp));
    }

    freeDeque(temp);
    return result;
}



void runDeque() {
    printf("\nEnter maximum deque size (1-1000): ");
    int maxSize = getValidInput(6, 1000);

    Deque* deque = fillDequeInteractive(maxSize);

    printf("\n-----------------------------\n");
    printf("Current deque (%d elements):\n", getDequeSize(deque));
    showDeque(deque);

    Deque* sixElements = getFirstThreeAndLastThreeElements(deque);
    if (sixElements->size > 0) {
        printf("\nFirst 3 and last 3 elements:\n");
        showDeque(sixElements);
    }
    freeDeque(sixElements);

    printf("\n-----------------------------\n");
    int firstNegative = findFirstNegativeFromRight(deque);
    if (firstNegative) {
        printf("First negative from right: %d\n", firstNegative);
        Deque* elementsUntilNegative = getElementsUntilFirstNegativeFromRight(deque);
        printf("\nElements until first negative:\n");
        showDeque(elementsUntilNegative);
        printf("\nRemaining size: %d\n", getDequeSize(deque));
        freeDeque(elementsUntilNegative);
    } else {
        printf("No negative elements found\n");
    }
    printf("-----------------------------\n");

    freeDeque(deque);
}