#include <stdio.h>
#include <stdlib.h>

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

char* getLine() {
    char *line = NULL; 
    int size = 0;     
    char ch;           

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *temp = realloc(line, size + 2);
        if (!temp) {
            free(line); 
            return NULL;
        }
        line = temp;
        line[size++] = ch;
    }

    if (line) {
        line[size] = '\0';
    } else {
        line = malloc(1);
        if (line) line[0] = '\0';
    }

    return line;
}

int inputStringMatrix(char ***string, int *rows) {
    printf("Enter number of rows: ");
    *rows = getValidInput(1, 2147483647);

    *string = (char **)malloc(*rows * sizeof(char *));
    if (*string == NULL) {
        printf("Memory allocation error for rows!\n");
        return 0;
    }

    printf("Enter strings:\n");
    for (int i = 0; i < *rows; i++) {
        printf("Enter string %d: ", i + 1);
        (*string)[i] = getLine();
        if ((*string)[i] == NULL) {
            printf("Memory allocation error for string %d!\n", i + 1);
            for (int j = 0; j < i; j++) {
                free((*string)[j]);
            }
            free(*string);
            return 0;
        }
    }

    return 1; 
}

void printStringMatrix(char **string, int rows) {
    for (int i = 0; i < rows; i++) {
        printf("%s\n", string[i]);
    }
}

int shortestWordLength(const char *str) {
    int minLength = 1000, currentLength = 0, i = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            currentLength++;
        } else if (currentLength > 0) {
            if (currentLength < minLength) {
                minLength = currentLength;
            }
            currentLength = 0;
        }

        i++;
    }

    if (currentLength > 0 && currentLength < minLength) {
        minLength = currentLength;
    }

    return minLength;
}

void merge(char **arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    char **leftArr = (char **)malloc(n1 * sizeof(char *));
    char **rightArr = (char **)malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) {
        leftArr[i] = (char *)malloc(256 * sizeof(char));
        for (int j = 0; arr[l + i][j] != '\0'; j++) {
            leftArr[i][j] = arr[l + i][j];
            leftArr[i][j + 1] = '\0';
        }
    }

    for (int i = 0; i < n2; i++) {
        rightArr[i] = (char *)malloc(256 * sizeof(char));
        for (int j = 0; arr[m + 1 + i][j] != '\0'; j++) {
            rightArr[i][j] = arr[m + 1 + i][j];
            rightArr[i][j + 1] = '\0';
        }
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (shortestWordLength(leftArr[i]) <= shortestWordLength(rightArr[j])) {
            arr[k] = leftArr[i++];
        } else {
            arr[k] = rightArr[j++];
        }
        k++;
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];

    free(leftArr);
    free(rightArr);
}

void mergesort(char **arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void freeStringMatrix(char **string, int rows) {
    for (int i = 0; i < rows; i++) {
        free(string[i]);
    }
    free(string);
}

int main() {
    char **stringMatrix = NULL;
    int rows = 0;

    inputStringMatrix(&stringMatrix, &rows);
    printf("Your original stringMatrix: \n");
    printStringMatrix(stringMatrix, rows);
    mergesort(stringMatrix, 0, rows - 1);
    printf("Your sorted stringMatrix: \n");
    printStringMatrix(stringMatrix, rows);
    freeStringMatrix(stringMatrix, rows);

    return 0;
}
