#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int getValidInput(int min, int max) {
    int num;
    char symbol;

    while (1) {
        char buffer[100];

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error!\nTry again: ");
            continue;
        }

        if (sscanf(buffer, "%d %c", &num, &symbol) != 1) {
            printf("Error! Please enter a valid integer.\nTry again: ");
            continue;
        }

        if (num < min || num > max) {
            printf("The input error: the number is not within the required range!\nTry again: ");
            continue;
        }

        return num;
    }
}

void manualInputMatrix(int rows, int cols, int matrix[100][100]) {
    printf("Enter the elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            matrix[i][j] = getValidInput(-2147483646, 2147483647);
        }
    }
}

void randomInputMatrix(int rows, int cols, int matrix[100][100]) {
    srand(time(NULL));
    printf("Enter min value: ");
    int min = getValidInput(-2147483646, 2147483647);
    printf("Enter max value: ");
    int max = getValidInput(-2147483646, 2147483647);

    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min; 
        }
    }
    printf("Matrix generated randomly.\n");
}

bool checkRowsForZero(int rows, int cols, int matrix[100][100]) {
    for (int i = 0; i < rows; i++) {
        bool hasZero = false;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (!hasZero) {
            return false;  
        }
    }
    return true;
}

void replaceNegativesWithZero(int rows, int cols, int matrix[100][100]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < 0) {
                matrix[i][j] = 0;
            }
        }
    }
}

void printMatrix(int rows, int cols, int matrix[100][100]) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[100][100];
    int rows, cols;

    printf("Enter the number of rows: ");
    rows = getValidInput(1, 2147483647);
    printf("Enter the number of columns: ");
    cols = getValidInput(1, 2147483647);

    int choice;
    printf("Choose the matrix input method:\n1. Manual input\n2. Random generation\n");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        manualInputMatrix(rows, cols, matrix);
    }
    else if (choice == 2) {
        randomInputMatrix(rows, cols, matrix);
    }
    else {
        printf("Error in choosing the input method.\n");
        return 1;
    }

    printMatrix(rows, cols, matrix);

    if (!checkRowsForZero(rows, cols, matrix)) {
        replaceNegativesWithZero(rows, cols, matrix);
        printf("After replacing negative elements with zero:\n");
        printMatrix(rows, cols, matrix);
    }
    else {
        printf("Every row contains at least one zero. No changes needed.\n");
    }

    return 0;
}
