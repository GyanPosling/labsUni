#include "rpnTask.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isOperation(char ch) {
    return ch == '+' || ch == '-'|| ch == '*' || ch == '/' || ch == '^';
}

bool isNum(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

int getPrecedence(char operation) {
    switch (operation) {
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
        case '^': return 4;
        case '(':
        case ')': return 1;
        default: return 0;
    }
}

bool prevIsOperation(const char *infixExpression, int index) {
    if (index == 0) return true;
    for (int i = index - 1; i >= 0; i--) {
        if (infixExpression[i] == ' ') continue;
        return isOperation(infixExpression[i]) || infixExpression[i] == '(';
    }
    return true;
}

char* parseRPN(const char* infixExpression) {
    CharStack operationStack;
    initCharStack(&operationStack);
    char *RPNExpression = (char*)malloc(200 * sizeof(char));
    if (!RPNExpression) return NULL;
    int j = 0;

    for (int i = 0; infixExpression[i] != '\0'; i++) {
        if (isdigit(infixExpression[i]) || (infixExpression[i] == '-' && prevIsOperation(infixExpression, i))) {
            if (infixExpression[i] == '-') {
                RPNExpression[j++] = '-';
                i++;
            }
            while (isdigit(infixExpression[i]) || infixExpression[i] == '.') {
                RPNExpression[j++] = infixExpression[i++];
            }
            RPNExpression[j++] = ' ';
            i--;
        } else if (infixExpression[i] == '(') {
            pushChar(&operationStack, infixExpression[i]);
        } else if (infixExpression[i] == ')') {
            while (!isCharStackEmpty(&operationStack) && peekChar(&operationStack) != '(') {
                RPNExpression[j++] = popChar(&operationStack);
                RPNExpression[j++] = ' ';
            }
            popChar(&operationStack);
        } else if (isOperation(infixExpression[i])) {
            while (!isCharStackEmpty(&operationStack) && getPrecedence(infixExpression[i]) <= getPrecedence(peekChar(&operationStack))) {
                RPNExpression[j++] = popChar(&operationStack);
                RPNExpression[j++] = ' ';
            }
            pushChar(&operationStack, infixExpression[i]);
        }
    }

    while (!isCharStackEmpty(&operationStack)) {
        RPNExpression[j++] = popChar(&operationStack);
        RPNExpression[j++] = ' ';
    }
    RPNExpression[j] = '\0';
    return RPNExpression;
}

double evaluateRPN(const char *rpnExpression) {
    DoubleStack numStack;
    initDoubleStack(&numStack);
    char *token = strtok((char*)rpnExpression, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            pushDouble(&numStack, atof(token));
        } else if (isOperation(token[0])) {
            double value2 = popDouble(&numStack);
            double value1 = popDouble(&numStack);
            double result = 0;
            switch (token[0]) {
                case '+': result = value1 + value2; break;
                case '-': result = value1 - value2; break;
                case '*': result = value1 * value2; break;
                case '/': 
                    if (value2 == 0.0) {
                        printf("Error: Division by zero!\n");
                        return NAN;
                    }
                    result = value1 / value2; 
                    break;
                case '^': result = pow(value1, value2); break;
            }
            pushDouble(&numStack, result);
        }
        token = strtok(NULL, " ");
    }
    return popDouble(&numStack);
}

int getErrorIndex(const char *infixExpression) {
    if (!infixExpression) return -1;

    int len = strlen(infixExpression);
    CharStack bracketStack;
    initCharStack(&bracketStack);

    bool prevWasOperator = true;
    bool prevWasOpenBracket = false;
    bool prevWasCloseBracket = false;

    for (int i = 0; i < len; i++) {
        char c = infixExpression[i];

        if (isspace(c)) continue; 

        if (!isNum(c) && !isOperation(c) && c != '(' && c != ')' && c != '.') {
            return i;
        }

        if (c == '(') {
            pushChar(&bracketStack, c);
            prevWasOpenBracket = true;
            prevWasOperator = true; 
        } else if (c == ')') {
            if (isCharStackEmpty(&bracketStack)) {
                return i;
            } else {
                popChar(&bracketStack);
            }
            prevWasOpenBracket = false;
            prevWasOperator = false;
        } else if (isOperation(c)) {
            if (prevWasOperator && !prevWasOpenBracket) {
                return i;
            }
            prevWasOperator = true;
            prevWasOpenBracket = false;
        } else if (isNum(c)) {
            if (c == '.') {
                if (i == len - 1 || !isdigit(infixExpression[i+1])) {
                    return i;
                }
                for (int j = i - 1; j >= 0 && isNum(infixExpression[j]); j--) {
                    if (infixExpression[j] == '.') {
                        return i;
                    }
                }
            }

            if (prevWasCloseBracket) {
                return i;
            }

            prevWasOperator = false;
            prevWasOpenBracket = false;
            prevWasCloseBracket = false;
        }
    }

    while (!isCharStackEmpty(&bracketStack)) {
        popChar(&bracketStack);
        return len - 1;
    }

    if (prevWasOperator && len > 0) {
        return len - 1;
    }

    return -1;
}

char* makeFileName() {
    printf("Enter filename (without extension): ");
    char* filename = initString();
    char* fullname = malloc(strlen(filename) + 5);
    strcpy(fullname, filename);
    strcat(fullname, ".txt");
    free(filename);
    return fullname;
}

void addToFile(char* file_name, char* expression) {
    FILE* file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Failed to open file: %s\n", file_name);
        return;
    }
    fprintf(file, "%s\n", expression);
    fclose(file);
}

void printError(const char* expression, int errorPos) {
    printf("%s\n", expression);
    for (int i = 0; i < errorPos; i++) {
        printf(" ");
    }
    printf("^\n");
}

void processExpression(const char* expression) {
    int errorIndex = getErrorIndex(expression);
    if (errorIndex != -1) {
        printf("\n--- Error Report ---\n");
        printf("Expression: %s\n", expression);
        printf("Error position: %d\n", errorIndex);
        printError(expression, errorIndex);
        printf("-------------------\n\n");
        return;
    }
    
    char* rpn = parseRPN(expression);
    
    printf("\n--- Processing ---\n");
    printf("Original: %s\n", expression);
    printf("RPN: %s\n", rpn);
    double result = evaluateRPN(rpn);
    printf("Result: %.2f\n", result);
    printf("-----------------\n\n");
    
    free(rpn);
}

void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        processExpression(line);
    }

    fclose(file);
}

void createNewFile(const char* filename) {
    printf("How many expressions do you want to enter? (1-%d): ", 100);
    int expressions_count = getValidInput(1, 100);
    printf("\n");
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create file: %s\n", filename);
        return;
    }
    
    for (int i = 0; i < expressions_count; i++) {
        printf("Expression %d: ", i+1);
        char* expression = initString();
        fprintf(file, "%s\n", expression);
        free(expression);
    }
    fclose(file);
}

void rpnTask() {
    printf("Reverse Polish Notation Calculator\n");
    printf("1. Enter expression manually\n");
    printf("2. Work with file\n");
    printf("Your choice (1-2): ");
    
    int choice = getValidInput(1, 2);
    printf("\n");
    
    if (choice == 1) {
        printf("Enter an infix expression: ");
        char *infix = initString();
        processExpression(infix);
        free(infix);
    } else {
        printf("1. Create new file\n");
        printf("2. Use existing file\n");
        printf("Your choice (1-2): ");
        
        int file_choice = getValidInput(1, 2);
        printf("\n");
        
        char* filename = makeFileName();
        
        if (file_choice == 1) {
            printf("How many expressions do you want to enter? (1-100): ");
            int expressions_count = getValidInput(1, 100);
            printf("\n");
            
            for (int i = 0; i < expressions_count; i++) {
                printf("Expression %d: ", i+1);
                char* expression = initString();
                addToFile(filename, expression);
                free(expression);
            }
        }
        
        processFile(filename);
        free(filename);
    }
}

