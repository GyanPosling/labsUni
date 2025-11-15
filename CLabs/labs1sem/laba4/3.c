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

void scanfMatrix(int arr[100][100], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter element [%d][%d]: ", i + 1, j + 1);
            arr[i][j] = getValidInput(-2147483646, 2147483647); 
        }
    }
}

void randomInputMatrix(int arr[100][100], int rows, int cols) {
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
            arr[i][j] = rand() % (max - min + 1) + min; 
        }
    }
    printf("Matrix generated randomly.\n");
}

void printMatrix(int arr[100][100], int rows, int cols) {
    printf("Your matrix: \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int sumElements(int arr[100][100], int rows, int cols) {
    int sum = 0;
    for (int i = rows / 2; i < rows; i++) {
        for (int j = cols / 2; j < cols; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}

int main() {
    int arr[100][100];
    int rows, cols;

    printf("Enter the number of rows: ");
    rows = getValidInput(1, 2147483647);
    printf("Enter the number of columns: ");
    cols = getValidInput(1, 2147483647);

    int choose;
    printf("Choose the input method for the matrix:\n1. Manual input\n2. Random generation\nEnter 1 or 2: ");
    choose = getValidInput(1, 2);

    if (choose == 1) {
        scanfMatrix(arr, rows, cols);
    } 
    else if (choose == 2) {
        randomInputMatrix(arr, rows, cols);
    } 
    else {
        printf("Error in choice.\n");
        return 1;
    }

    printMatrix(arr, rows, cols);

    int sum = sumElements(arr, rows, cols);
    printf("Sum of elements in the fourth quadrant = %d\n", sum);

    return 0;
}
