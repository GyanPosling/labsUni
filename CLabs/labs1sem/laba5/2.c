#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int getValidInput(int min, int max) {
    int num;
    char symbol;

    while (1) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error! Try again: ");
            continue;
        }

        if (sscanf(buffer, "%d %c", &num, &symbol) != 1) {
            printf("Error! Try again: ");
            continue;
        }

        if (num < min || num > max) {
            printf("The input error: the number is not within the required range! Try again: ");
            continue;
        }

        return num;
    }
}

int** inputArray(int** cols, int* rows) {
    printf("Enter number of rows: ");
    *rows = getValidInput(1, 2147483647);

    *cols = (int*)malloc((*rows) * sizeof(int));
    if (*cols == NULL) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    int** arr = (int**)malloc((*rows) * sizeof(int*));
    if (arr == NULL) {
        printf("Memory allocation error!\n");
        free(*cols);
        return NULL;
    }

    printf("Choose input method:\n1. Manual input\n2. Random values\nEnter your choice: ");
    int choice = getValidInput(1, 2);

    if (choice == 1) {
        for (int i = 0; i < *rows; i++) {
            printf("Enter the number of elements in row %d: ", i + 1);
            (*cols)[i] = getValidInput(1, 2147483647);

            arr[i] = (int*)malloc((*cols)[i] * sizeof(int));
            if (arr[i] == NULL) {
                for (int k = 0; k < i; k++) free(arr[k]);
                free(arr);
                free(*cols);
                return NULL;
            }

            for (int j = 0; j < (*cols)[i]; j++) {
                printf("Enter element [%d][%d]: ", i + 1, j + 1);
                arr[i][j] = getValidInput(-2147483646, 2147483647);
            }

            arr[i][(*cols)[i] - 1] = 100;
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
            (*cols)[i] = (rand() % 10) + 1;
            arr[i] = (int*)calloc((*cols)[i], sizeof(int));
            if (arr[i] == NULL) {
                for (int k = 0; k < i; k++) free(arr[k]);
                free(arr);
                free(*cols);
                return NULL;
            }

            for (int j = 0; j < (*cols)[i]; j++) {
                arr[i][j] = rand() % (max - min + 1) + min;
            }

            arr[i][(*cols)[i] - 1] = 100;
        }
    
    }

    return arr;
}

int* deleteNegativeElements(int* arr, int* size) {
    int newSize = 0;
    int* temp = (int*)malloc((*size) * sizeof(int));

    for (int i = 0; i < *size - 1; i++) {
        if (arr[i] >= 0) {
            temp[newSize++] = arr[i];
        }
    }

    temp[newSize++] = arr[*size - 1];
    *size = newSize;
    temp = (int*)realloc(temp, newSize * sizeof(int));

    return temp;
}

void deleteNegative(int** arr, int* cols, int rows) {
    for (int i = 0; i < rows; i++) {
        arr[i] = deleteNegativeElements(arr[i], &cols[i]);
    }
}

void printMatrix(int** arr, int* cols, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols[i]; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int*** arr, int** cols, int rows) {
    for (int i = 0; i < rows; i++) {
        free((*arr)[i]);
    }
    free(*arr);
    free(*cols);
}

int main() {
    int* cols = NULL;
    int rows = 0;
    int** matrix = inputArray(&cols, &rows);

    printf("\nOriginal matrix:\n");
    printMatrix(matrix, cols, rows);

    deleteNegative(matrix, cols, rows);

    printf("\nMatrix after removing negative elements:\n");
    printMatrix(matrix, cols, rows);

    freeMatrix(&matrix, &cols, rows);

    return 0;
}
