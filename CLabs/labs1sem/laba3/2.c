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

void manualInput(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter the %d element of the array: ", i + 1);
        array[i] = getValidInput(-2147483648, 2147483647);
    }
}

void randomInput(int array[], int size, int minValue, int maxValue) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
}

void handleArrayInput(int array[], int* size) {
    printf("Enter the number of elements in the array (at least 4): ");
    *size = getValidInput(4, 2147483647);
    while (*size < 4) {
        printf("The number of elements must be at least 4. Try again: ");
        *size = getValidInput(4, 2147483647);
    }

    int choice;
    printf("Choose how to fill the array (1 - manual input, 2 - random input): ");
    choice = getValidInput(1, 2);
    while (choice != 1 && choice != 2) {
        printf("Invalid choice. Enter 1 for manual input or 2 for random input: ");
        choice = getValidInput(1, 2);
    }

    if (choice == 1) {
        manualInput(array, *size);
    } else {
        int minValue, maxValue;
        printf("Enter the minimum value for random numbers: ");
        minValue = getValidInput(-2147483648, 2147483647);
        printf("Enter the maximum value for random numbers: ");
        maxValue = getValidInput(minValue, 2147483647);
        randomInput(array, *size, minValue, maxValue);
        printf("\nThe array was filled with random numbers.\n");
    }
}

void printArray(const char* message, int array[], int size) {
    printf("%s", message);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int findNthSmallest(int array[], int size, int n) {
    int min, minIndex;
    for (int i = 0; i < n; i++) {
        min = 2147483647;
        minIndex = -1;
        for (int j = 0; j < size; j++) {
            if (array[j] != 2147483647 && array[j] < min) {
                min = array[j];
                minIndex = j;
            }
        }
        array[minIndex] = 2147483647;
    }
    return min;
}

int main() {
    int array[100];
    int size;

    handleArrayInput(array, &size);

    printArray("Your array: ", array, size);

    if (size >= 4) {
        int fourthSmallest = findNthSmallest(array, size, 4);
        printf("The 4th smallest element in the array = %d\n", fourthSmallest);
    } else {
        printf("The array is too small to find the 4th smallest element.\n");
    }

    return 0;
}
