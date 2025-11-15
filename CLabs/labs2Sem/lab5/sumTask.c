#include "stacksImplement.h"
#include "validators.h"
#include "sumtask.h"
#include <stdio.h>

IntStack fillStack() {
    IntStack s;
    initIntStack(&s);
    
    int size;
    printf("How many elements to add to stack? ");
    size = getValidInput(1, 100);

    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        int num;
        scanf("%d", &num);
        pushInt(&s, num);
    }
    return s;
}

int sumOfStackElements(IntStack* s) {
    int sum = 0;
    IntObject* current = s->top;
    while (current != NULL) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

void sumTask() {
    IntStack s = fillStack();
    printf("Sum of stack elements: %d\n", sumOfStackElements(&s));
    freeIntStack(&s);
}