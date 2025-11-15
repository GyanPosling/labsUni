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

void merge(int* arr, int* indices, int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
 
    int* L1 = (int*)malloc(n1 * sizeof(int)); 
    int* L2 = (int*)malloc(n1 * sizeof(int)); 
    int* R1 = (int*)malloc(n2 * sizeof(int)); 
    int* R2 = (int*)malloc(n2 * sizeof(int)); 
 
    for (i = 0; i < n1; i++) { 
        L1[i] = arr[l + i]; 
        L2[i] = indices[l + i]; 
    } 
 
    for (j = 0; j < n2; j++) { 
        R1[j] = arr[m + j + 1]; 
        R2[j] = indices[m + j + 1]; 
    } 
 
    i = 0; 
    j = 0; 
    k = l; 
 
    while (i < n1 && j < n2) { 
        if (L1[i] <= R1[j]) { 
            arr[k] = L1[i]; 
            indices[k] = L2[i]; 
            i++; 
        } else { 
            arr[k] = R1[j]; 
            indices[k] = R2[j]; 
            j++; 
        } 
        k++; 
    } 
 
    while (i < n1) { 
        arr[k] = L1[i]; 
        indices[k] = L2[i]; 
        i++; 
        k++; 
    } 
 
    while (j < n2) { 
        arr[k] = R1[j]; 
        indices[k] = R2[j]; 
        j++; 
        k++; 
    } 
 
    free(L1); 
    free(L2); 
    free(R1); 
    free(R2); 
} 
 
void merge_sort(int* arr, int* indices, int l, int r) { 
    if (l < r) { 
        int mid = l + (r - l) / 2; 
        merge_sort(arr, indices, l, mid); 
        merge_sort(arr, indices, mid + 1, r); 
        merge(arr, indices, l, mid, r); 
    } 
} 

int sumOfEvenEl(int* arr, int size) { 
    int sum = 0; 
    for (int i = 0; i < size; i++) { 
        if (arr[i] % 2 == 0) { 
            sum += arr[i]; 
        } 
    } 
    return sum; 
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int** inputMatrix(int rows, int cols, int flag) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
    }

    if (flag == 1) { 
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("Enter element [%d][%d]: ", i + 1, j + 1);
                matrix[i][j] = getValidInput(-2147483646, 2147483647);
            }
        }
    } else if (flag == 2) {
        srand(time(NULL));
        int min, max;
        printf("Enter minimum value for your random matrix: ");
        min = getValidInput(-2147483646, 2147483647);
        printf("Enter maximum value for your random matrix: ");
        max = getValidInput(-2147483646, 2147483647);

        if (min > max) {
            swap(&min, &max);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = (rand() % (max - min + 1)) + min;
            }
        }
    }

    return matrix;
}


void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sortMatrix(int** arr, int rows, int cols) { 
    int* indices = (int*)malloc(cols * sizeof(int)); 
    for (int i = 0; i < cols; i++) { 
        indices[i] = i; 
    } 

    int* sumEven = (int*)malloc(cols * sizeof(int)); 
    for (int j = 0; j < cols; j++) { 
        int* column = (int*)malloc(rows * sizeof(int)); 
        for (int i = 0; i < rows; i++) { 
            column[i] = arr[i][j]; 
        } 
        sumEven[j] = sumOfEvenEl(column, rows); 
        free(column); 
    } 

    merge_sort(sumEven, indices, 0, cols - 1); 

    int** tempMatrix = (int**)malloc(rows * sizeof(int*)); 
    for (int i = 0; i < rows; i++) { 
        tempMatrix[i] = (int*)malloc(cols * sizeof(int)); 
    } 

    for (int j = 0; j < cols; j++) { 
        int colIndex = indices[j]; 
        for (int i = 0; i < rows; i++) { 
            tempMatrix[i][j] = arr[i][colIndex]; 
        } 
    } 

    for (int j = 0; j < cols; j++) { 
        for (int i = 0; i < rows; i++) { 
            arr[i][j] = tempMatrix[i][j]; 
        } 
    } 

    for (int i = 0; i < rows; i++) { 
        free(tempMatrix[i]); 
    } 
    free(tempMatrix); 
    free(sumEven); 
    free(indices); 
} 

void freeMatrix(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() { 
    int rows, cols; 
    printf("Enter number of rows: ");
    rows = getValidInput(1, 2147483647);
    printf("Enter number of columns: ");
    cols = getValidInput(1, 2147483647);

    int flag;
    printf("Choose input method:\n1. Manual Input\n2. Random Fill\n");
    flag = getValidInput(1, 2);


    int** matrix = inputMatrix(rows, cols, flag);

    printf("Your unsorted matrix: \n");
    printMatrix(matrix, rows, cols);

    sortMatrix(matrix, rows, cols);

    printf("Your sorted matrix: \n");
    printMatrix(matrix, rows, cols);

    freeMatrix(matrix, rows);

    return 0; 
}
