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

void swap (int*a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void RandomInput(int arr[100][100], int rows, int cols) {
    srand(time(NULL));
    printf("Enter min: ");
    int min = getValidInput(-2147483646, 2147483647);
    printf("Enter max: ");
    int max = getValidInput(-2147483646, 2147483647);
    if(min > max){
        swap(&min, &max);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void ManualInput(int arr[100][100], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter element [%d][%d]: ", i + 1, j + 1);
            arr[i][j] = getValidInput(-2147483646, 2147483647);
        }
    }
}

void PrintMatrix(int arr[100][100], int rows, int cols) {
    printf("Your matrix: \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int FindCountSameElements(int* row, int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (row[i] == row[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

void BubbleSortRows(int matrix[][100], int cols, int rows) {
    int temp[100];
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - 1 - i; j++) {
            if (FindCountSameElements(matrix[j], cols) > FindCountSameElements(matrix[j + 1], cols)) {
                for (int k = 0; k < cols; k++) {
                    temp[k] = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp[k];
                }
            }
        }
    }
}

int FindFirstNonNegativeColumn(int arr[100][100], int rows, int cols) {
    for (int j = 0; j < cols; j++) {
        int hasNegative = 0;
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] < 0) {
                hasNegative = 1;
                break;
            }
        }
        if (!hasNegative) {
            return j + 1;
        }
    }
    return -1;
}

void ProcessMatrixInput(int arr[100][100], int rows, int cols) {

    printf("Choose the input method for the matrix:\n1. Manual input\n2. Random number generation\nEnter 1 or 2: ");
    int choice = getValidInput(1, 2);

    if (choice == 1) {
        ManualInput(arr, rows, cols);
    } else if (choice == 2) {
        RandomInput(arr, rows, cols);
    }
}

int main() {
    int arr[100][100];

    printf("Enter the number of rows: ");
    int rows = getValidInput(1, 2147483647);
    printf("Enter the number of columns: ");
    int cols = getValidInput(1, 2147483647);

    ProcessMatrixInput(arr, rows, cols);

    printf("Your unsorted matrix: \n");
    PrintMatrix(arr, rows, cols);

    BubbleSortRows(arr, cols, rows);

    printf("Your sorted matrix: \n");
    PrintMatrix(arr, rows, cols);

    int firstNonNegativeColumn = FindFirstNonNegativeColumn(arr, rows, cols);
    if (firstNonNegativeColumn != -1) {
        printf("The first column without negative elements is: %d\n", firstNonNegativeColumn);
    } else {
        printf("No columns without negative elements.\n");
    }

    return 0;
}
