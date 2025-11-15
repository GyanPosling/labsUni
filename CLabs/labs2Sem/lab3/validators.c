#include "validators.h"


char* initString() {
    char* str = NULL;
    char ch;
    int length = 0;
    int capacity = 10;

    str = malloc(sizeof(char) * capacity);
    if (str == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    while ((ch = getchar()) != '\n') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
            if (str == NULL) {
                printf("Memory reallocation failed\n");
                exit(1);
            }
        }
        str[length++] = ch;
    }

    str[length] = '\0';
    return str;
}

int getValidInput(int min, int max) {
    int num;
    char symbol;

    while (1) {
        char buffer[100];

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input!\nTry again: ");
            continue;
        }

        if (sscanf(buffer, "%d %c", &num, &symbol) != 1) {
            printf("Invalid input! Please enter a number.\nTry again: ");
            continue;
        }

        if (num < min || num > max) {
            printf("The number is not within the range [%d, %d]!\nTry again: ", min, max);
            continue;
        }

        return num;
    }
}

char getValidCharInteger(int min, int max) {
    char num;
    int valid = 0;

    while (!valid) {
        printf("Enter a number between %d and %d: ", min, max);
        if (scanf("%hhd", &num) == 1) {
            if (num >= min && num <= max) {
                valid = 1;
            } else {
                printf("The number must be between %d and %d.\n", min, max);
            }
        } else {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
        }
    }
    return num;
}

