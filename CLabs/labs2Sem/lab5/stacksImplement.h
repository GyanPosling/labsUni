#ifndef STACK_H
#define STACK_H

typedef struct IntObject {
    int value;
    struct IntObject* next;
} IntObject;

typedef struct {
    IntObject* top;
    int size;
} IntStack;

typedef struct DoubleObject {
    double value;
    struct DoubleObject* next;
} DoubleObject;

typedef struct {
    DoubleObject* top;
    int size;
} DoubleStack;

typedef struct CharNode {
    char value;
    struct CharNode* next;
} CharNode;

typedef struct {
    CharNode* top;
    int size;
} CharStack;

void initIntStack(IntStack* s);
int isIntStackEmpty(IntStack* s);
void pushInt(IntStack* s, int value);
int popInt(IntStack* s);
int peekInt(IntStack* s);
void freeIntStack(IntStack* s);

void initDoubleStack(DoubleStack* s);
int isDoubleStackEmpty(DoubleStack* s);
void pushDouble(DoubleStack* s, double value);
double popDouble(DoubleStack* s);
double peekDouble(DoubleStack* s);
void freeDoubleStack(DoubleStack* s);

void initCharStack(CharStack* s);
int isCharStackEmpty(CharStack* s);
void pushChar(CharStack* s, char value);
char popChar(CharStack* s);
char peekChar(CharStack* s);
void freeCharStack(CharStack* s);

#endif