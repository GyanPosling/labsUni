#ifndef MERGETASK_H
#define MERGETASK_H

#include "stacksImplement.h"

void insertSorted(IntStack* s, int num);
IntStack fillStackInOrder();
void printfStackRecursive(IntStack *stack);
void printStackInfo(IntStack *stack);
IntStack *merge(IntStack *stack1, IntStack *stack2);
void mergeTask();

#endif