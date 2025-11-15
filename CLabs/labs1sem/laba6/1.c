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
            printf("Error!\n Try again: ");
            continue;
        }

        if (num < min || num > max) {
            printf("The input error: the number is not within the required range!\n Try again: ");
            continue;
        }

        return num;
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* inputArray(int size, int flag) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (flag == 1) { 
        for (int i = 0; i < size; i++) {
            printf("Enter element %d: ", i + 1);
            arr[i] = getValidInput(-2147483646, 2147483647);
        }
    } else if (flag == 2) { 
        srand(time(NULL)); 
		printf("Enter min value in your random array: ");
		int min = getValidInput(-2147483646, 2147483647);
		printf("Enter max value in your random array: ");
		int max = getValidInput(-2147483646, 2147483647);
		if(min > max)
			swap(&min, &max);
        for (int i = 0; i < size; i++) {
            arr[i] = (rand() % (max - min + 1)) + min;; 
        }
    }

    return arr;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int indexOfLastPositiveElement(int* arr, int size) {
    int lastIndex = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            lastIndex = i;
        }
    }
    return lastIndex;
}

void shellSort(int* arr, int size) {
    int lastPositiveInd = indexOfLastPositiveElement(arr, size);
    if (lastPositiveInd == -1) return; 
    for (int gap = (lastPositiveInd + 1) / 2; gap > 0; gap /= 2) {
        for (int i = gap; i <= lastPositiveInd; i++) {
            if (arr[i] % 2 != 0) {
                for (int j = i; j >= gap && arr[j - gap] % 2 != 0; j -= gap) {
                    if (arr[j - gap] > arr[j]) {
                        swap(&arr[j], &arr[j - gap]);
                    }
                }
            }
        }
    }
}


int main() {
    int size;
    printf("Enter size of the array: ");
    size = getValidInput(0, 2147483646);  

    int flag;
    printf("Choose input method:\n1. Manual input\n2. Random values\nEnter your choice: ");
    flag = getValidInput(1, 2); 

    int* arr = inputArray(size, flag); 

    printf("Original array: ");
    printArray(arr, size);

    shellSort(arr, size);

    printf("Array after sorting:\n");
    printArray(arr, size);

    free(arr);
    return 0;
}
