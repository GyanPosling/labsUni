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
        array[i] = getValidInput(-2147483648, 2147483647);  // Handling large integer range for inputs
    }
}

void randomInput(int array[], int size, int minValue, int maxValue) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (maxValue - minValue + 1) + minValue;
    }
}

void printArray(int array[], int size) {
    printf("You entered the following elements of the array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}

int calculatePositiveProduct(int array[], int size) {
    int product = 1;
    int hasPositive = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > 0) {
            product *= array[i];
            hasPositive = 1;
        }
    }
    return hasPositive ? product : 0;
}

int findMinElementIndex(int array[], int size) {
    int min = array[0], minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int sumBeforeMinElement(int array[], int minIndex) {
    int sum = 0;
    for (int i = 0; i < minIndex; i++) {
        sum += array[i];
    }
    return sum;
}

void handleArrayInput(int array[], int* size) {

    printf("Enter the number of elements in the array (maximum 100): ");
    *size = getValidInput(1, 100);

    int choice;
    printf("Choose how to fill the array (1 - manual input, 2 - random input): ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        manualInput(array, *size);
    } else {
        int minValue, maxValue;
        printf("Enter the minimum value for random numbers: ");
        minValue = getValidInput(-2147483648, 2147483647);
        printf("Enter the maximum value for random numbers: ");
        maxValue = getValidInput(minValue, 2147483647);

        while (minValue > maxValue) {
            printf("Error. Minimum value cannot be greater than maximum value.\n");
            printf("Enter the minimum value for random numbers: ");
            minValue = getValidInput(-2147483648, 2147483647);
            printf("Enter the maximum value for random numbers: ");
            maxValue = getValidInput(minValue, 2147483647);
        }
        randomInput(array, *size, minValue, maxValue);
        printf("The array was filled with random numbers.\n");
    }
}

int main() {
    int array[100];
    int size;

    handleArrayInput(array, &size);
    printArray(array, size);

    int product = calculatePositiveProduct(array, size);
    printf("The product of positive elements: %d\n", product);

    int minIndex = findMinElementIndex(array, size);
    printf("Minimum number = %d\n", array[minIndex]);

    int sumBeforeMin = sumBeforeMinElement(array, minIndex);
    printf("The sum of all elements before the minimum = %d\n", sumBeforeMin);

    return 0;
}
