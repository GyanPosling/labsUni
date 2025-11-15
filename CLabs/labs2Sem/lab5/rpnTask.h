#ifndef POLISH_H
#define POLISH_H

#include "stacksImplement.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include<string.h>
#include "validators.h"

bool isOperation(char ch);
bool isNum(char c);
int getPrecedence(char operation);
bool prevIsOperation(const char* infixExpression, int index);
char* parseRPN(const char* infixExpression);
double evaluateRPN(const char* rpnExpression);
int getErrorIndex(const char* infixExpression);
void printArray(int* array);
char* makeFileName();
void addToFile(char* file_name, char* expression);
void createExpressions(char* file_name);
void processFileExpressions(char* file_name);
void rpnTask();


#endif