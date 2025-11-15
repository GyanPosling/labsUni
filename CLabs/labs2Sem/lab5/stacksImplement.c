#include "stacksImplement.h"
#include <stdio.h>
#include <stdlib.h>

void initIntStack(IntStack* s) {
    s->top = NULL;
    s->size = 0;
}

int isIntStackEmpty(IntStack* s) {
    return s->top == NULL;
}

void pushInt(IntStack* s, int value) {
    IntObject* new_obj = (IntObject*)malloc(sizeof(IntObject));
    if (new_obj == NULL) {
        printf("Memory allocation error!\n");
        return;
    }
    new_obj->value = value;
    new_obj->next = s->top;
    s->top = new_obj;
    s->size++;
}

int popInt(IntStack* s) {
    if (isIntStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    IntObject* temp = s->top;
    int value = temp->value;
    s->top = temp->next;
    free(temp);
    s->size--;
    return value;
}

int peekInt(IntStack* s) {
    if (isIntStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->top->value;
}

void freeIntStack(IntStack* s) {
    while (!isIntStackEmpty(s)) {
        popInt(s);
    }
}

void initDoubleStack(DoubleStack* s) {
    s->top = NULL;
    s->size = 0;
}

int isDoubleStackEmpty(DoubleStack* s) {
    return s->top == NULL;
}

void pushDouble(DoubleStack* s, double value) {
    DoubleObject* new_obj = (DoubleObject*)malloc(sizeof(DoubleObject));
    if (new_obj == NULL) {
        printf("Memory allocation error!\n");
        return;
    }
    new_obj->value = value;
    new_obj->next = s->top;
    s->top = new_obj;
    s->size++;
}

double popDouble(DoubleStack* s) {
    if (isDoubleStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    DoubleObject* temp = s->top;
    double value = temp->value;
    s->top = temp->next;
    free(temp);
    s->size--;
    return value;
}

double peekDouble(DoubleStack* s) {
    if (isDoubleStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->top->value;
}

void freeDoubleStack(DoubleStack* s) {
    while (!isDoubleStackEmpty(s)) {
        popDouble(s);
    }
}

void initCharStack(CharStack* s) {
    s->top = NULL;
    s->size = 0;
}

int isCharStackEmpty(CharStack* s) {
    return s->top == NULL;
}

void pushChar(CharStack* s, char value) {
    CharNode* new_obj = (CharNode*)malloc(sizeof(CharNode));
    if (new_obj == NULL) {
        printf("Memory allocation error!\n");
        return;
    }
    new_obj->value = value;
    new_obj->next = s->top;
    s->top = new_obj;
    s->size++;
}

char popChar(CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Stack is empty!\n");
        return '\0';
    }
    CharNode* temp = s->top;
    char value = temp->value;
    s->top = temp->next;
    free(temp);
    s->size--;
    return value;
}

char peekChar(CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Stack is empty!\n");
        return '\0';
    }
    return s->top->value;
}

void freeCharStack(CharStack* s) {
    while (!isCharStackEmpty(s)) {
        popChar(s);
    }
}