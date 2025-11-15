#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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

void RandomInput(int array[], int* size) {
    printf("Enter the number of elements in the array: ");
    *size = getValidInput(1, 100); 
    int min, max;
    printf("Enter the minimum value: ");
    min = getValidInput(INT_MIN, INT_MAX); 
    printf("Enter the maximum value: ");
    max = getValidInput(min, INT_MAX); 

    srand(time(NULL));
    for (int i = 0; i < *size; i++) {
        array[i] = rand() % (max - min + 1) + min; 
    }
}

void ScanfArray(int array[], int* n) {
    printf("Enter the number of elements in the array: ");
    *n = getValidInput(1, 100); 
    for (int i = 0; i < *n; i++) {
        printf("Enter element %d of the array: ", i + 1);
        while (1) {
            if (scanf("%d", &array[i]) != 1) {
                while (getchar() != '\n'); 
                printf("Invalid input. Enter element %d again: ", i + 1);
            }
            else {
                break;
            }
        }
    }
}

void PrintArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n"); 
}

int IsInArray(int element, int array[], int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] == element) {
            return 1;
        }
    }
    return 0; 
}

int IsMaxElementInSecondArray(int array1[], int n, int array2[], int k) {
    int max = INT_MIN;
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (!IsInArray(array1[i], array2, k)) {
            if (array1[i] > max) {
                max = array1[i];
                found = 1; 
            }
        }
    }
    return found ? max : INT_MIN; 
}

void ProcessArray(int array[], int* n) {
    int choice;
    printf("Choose the method for the array:\n1. Manual input\n2. Random number generation\nEnter 1 or 2: ");
    choice = getValidInput(1, 2); 

    if (choice == 1) {
        ScanfArray(array, n);
    }
    else if (choice == 2) {
        RandomInput(array, n);
    }
    else {
        printf("Invalid choice. Program will terminate.\n");
        exit(1);
    }
}

int main() {
    int arrayN[100], arrayK[100];
    int n, k;

    ProcessArray(arrayN, &n);
    PrintArray(arrayN, n);

    ProcessArray(arrayK, &k);
    PrintArray(arrayK, k);

    int result = IsMaxElementInSecondArray(arrayN, n, arrayK, k);
    if (result == INT_MIN) {
        printf("\nNo such element found.\n");
    }
    else {
        printf("\nAnswer = %d\n", result);
    }

    return 0;
}
