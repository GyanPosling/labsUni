#include <stdio.h>
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
            printf("Error!\nTry again: ");
            continue;
        }

        if (num < min || num > max) {
            printf("The input error: the number is not within the required range!\nTry again: ");
            continue;
        }

        return num;
    }
}

void shiftLeft(int* row, int cols, int k) {
    int* temp = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        temp[i] = row[i];
    }
    for (int i = 0; i < cols - k; i++) {
        row[i] = row[i + k];
    }
    for (int i = 0; i < k; i++) {
        row[cols - k + i] = temp[i];
    }
    free(temp);
}

int** scanfMatrix(int* rows, int* cols) {
    printf("Enter number of rows: ");
    *rows = getValidInput(1, 2147483647);

    printf("Enter number of columns: ");
    *cols = getValidInput(1, 2147483647);

    int** arr = (int**)malloc(*rows * sizeof(int*));
    if (arr == NULL) {
        printf("Memory allocation error!\n");
        return NULL; 
    }

    for (int i = 0; i < *rows; i++) {
        arr[i] = (int*)malloc(*cols * sizeof(int));
        if (arr[i] == NULL) {
            printf("Memory allocation error!\n");
            return NULL;
        }
    }

    printf("Choose input method:\n1. Manual input\n2. Random values\nEnter your choice: ");
    int choice = getValidInput(1, 2);

    if (choice == 1) {
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                printf("Enter element [%d][%d]: ", i + 1, j + 1);
                arr[i][j] = getValidInput(-2147483646, 2147483647);
            }
        }
    } else if (choice == 2) {
        printf("Enter the minimum random value: ");
        int min = getValidInput(-2147483646, 2147483647);
        printf("Enter the maximum random value: ");
        int max = getValidInput(-2147483646, 2147483647);

        if (min > max) {
            int temp = min;
            min = max;
            max = temp;
        }

        srand(time(NULL));
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                arr[i][j] = rand() % (max - min + 1) + min;
            }
        }
    }

    return arr; 
}

void printMatrix(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    int rows, cols;

    int** matrix = scanfMatrix(&rows, &cols);

    printf("Enter k: ");
    int k = getValidInput(0, cols);

    printf("Original matrix:\n");
    printMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        shiftLeft(matrix[i], cols, k);
    }

    printf("Matrix after shifting:\n");
    printMatrix(matrix, rows, cols);

    freeMatrix(matrix, rows);

    return 0;
}
