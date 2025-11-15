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

void swap(int *a, int*b){
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
        printf("%d  ", arr[i]);
    }
    printf("\n");
}


int countUniqueElements(int* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        short isDuplicate = 0;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            count++;
        }
    }
    return count;
}


int* removeDuplicates(int* arr, int size, int* newSize) {
    *newSize = countUniqueElements(arr, size);
    int* newArr = (int*)malloc(*newSize * sizeof(int));
    if (newArr == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        short isDuplicate = 0;
        for (int j = 0; j < index; j++) {
            if (arr[i] == newArr[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            newArr[index++] = arr[i];
        }
    }
    return newArr;
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

    int newSize;
    int* newArr = removeDuplicates(arr, size, &newSize);
    printf("Final array after removing duplicates: ");
    printArray(newArr, newSize);

    free(arr);
    free(newArr);

    return 0;
}
