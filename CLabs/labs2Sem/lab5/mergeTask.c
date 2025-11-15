#include "stacksImplement.h"
#include "validators.h"
#include "mergetask.h"
#include <stdio.h>
#include <stdlib.h>

void insertSorted(IntStack* s, int num) {
    if (isIntStackEmpty(s) || peekInt(s) <= num) {
        pushInt(s, num);
    } else {
        int temp = popInt(s);
        insertSorted(s, num);
        pushInt(s, temp);
    }
}

IntStack fillStackInOrder() {
    IntStack stack;
    initIntStack(&stack);
    int size;
    printf("How many elements to add to stack? ");
    size = getValidInput(1, 100);

    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        int num;
        scanf("%d", &num);
        insertSorted(&stack, num);
    }
    return stack;
}

void printfStackRecursive(IntStack *stack){
    if (isIntStackEmpty(stack))
        return;
    int num = popInt(stack);
    printf("%d ", num);
    printfStackRecursive(stack);
    pushInt(stack, num);
}

void printStackInfo(IntStack *stack){
    printf("Stack info: \n");
    printfStackRecursive(stack);
    printf("\n");
}

IntStack *merge(IntStack *stack1, IntStack *stack2) {
    IntStack *finalStack = (IntStack*)malloc(sizeof(IntStack));
    initIntStack(finalStack);
    while(!isIntStackEmpty(stack1) && !isIntStackEmpty(stack2)) {
        if (peekInt(stack1) <= peekInt(stack2))
            pushInt(finalStack, popInt(stack2));
        else
            pushInt(finalStack, popInt(stack1));
    }
    while(!isIntStackEmpty(stack1))
        pushInt(finalStack, popInt(stack1));
    while(!isIntStackEmpty(stack2))
        pushInt(finalStack, popInt(stack2)); 
    return finalStack;

}

void mergeTask() {
    printf("Init first stack: \n");
    IntStack stack1 = fillStackInOrder();
    
    printf("Init second stack: \n");
    IntStack stack2 = fillStackInOrder();
    
    printf("Stack 1 info: \n");
    printStackInfo(&stack1);
    
    printf("Stack 2 info: \n");
    printStackInfo(&stack2);
    
    IntStack *finalStack = merge(&stack1, &stack2);
    
    printf("Final Stack info: \n");
    printStackInfo(finalStack);
    
    freeIntStack(&stack1);
    freeIntStack(&stack2);
    freeIntStack(finalStack);
    free(finalStack);
}