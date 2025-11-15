#include "func.h"

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

char* initNameOfFile() {
    char* str = NULL;
    char ch;

    int length = 0;
    int capacity = 10;

    str = malloc(sizeof(char) * capacity);

    while ((ch = getchar()) != '\n') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }

        str[length++] = ch;
    }
    str[length] = '\0';

    if (length < 4 || strncmp(str + length - 4, ".bin", 4) != 0) {
        strcat(str, ".bin");
    }

    return str;
}

void initFileByHand(const char* filename, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror(filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("Enter number: ");
        int num = getValidInput(INT_MIN, INT_MAX);
        fwrite(&num, sizeof(int), 1, file);
    }

    fclose(file);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initRandomFile(const char* filename, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror(filename);
        return;
    }

    srand(time(NULL));

    printf("Enter min value in your random array: ");
    int min = getValidInput(INT_MIN, INT_MAX);
    printf("Enter max value in your random array: ");
    int max = getValidInput(INT_MIN, INT_MAX);

    if (min > max) {
        swap(&min, &max);
    }

    for (int i = 0; i < size; i++) {
        int num = (rand() % (max - min + 1)) + min;
        fwrite(&num, sizeof(int), 1, file);
    }

    fclose(file);
}

void printFileInformation(const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror(fileName);
        return;
    }

    int num;
    printf("Numbers in file: ");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}

// Реализации функций для задач 1-4
void task1(int argc, char *argv[]) {
    char *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Enter name of file: ");
        filename = initNameOfFile();
    }

    printf("Enter size: ");
    int size = getValidInput(1, 100);
    int choice;
    printf("Choose a method to fill the file:\n");
    printf("1. Fill file manually\n");
    printf("2. Fill file with random numbers\n");
    printf("Enter your choice (1 or 2): ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        printf("Initializing file with manual input:\n");
        initFileByHand(filename, size);
    } else if (choice == 2) {
        printf("Initializing file with random input:\n");
        initRandomFile(filename, size);
    }

    printFileInformation(filename);

    if (argc <= 1) {
        free(filename);
    }
}

int findBreakPoint(char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror(fileName);
        return -1;
    }

    int prev, current, position = 0;
    if (fread(&prev, sizeof(int), 1, file)) {
        position++;
        while (fread(&current, sizeof(int), 1, file)) {
            if (current < prev) {
                fclose(file);
                return position - 1;
            }
            position++;
            prev = current;
        }
    } else {
        perror(fileName);
        fclose(file);
        return -1;
    }
    fclose(file);
    return -1;
}

void task2(int argc, char *argv[]) {
    char *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Enter name of file: ");
        filename = initNameOfFile();
    }

    printf("Enter size: ");
    int size = getValidInput(1, 100);
    int choice;
    printf("Choose a method to fill the file:\n");
    printf("1. Fill file manually\n");
    printf("2. Fill file with random numbers\n");
    printf("Enter your choice (1 or 2): ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        printf("Initializing file with manual input:\n");
        initFileByHand(filename, size);
    } else if (choice == 2) {
        printf("Initializing file with random input:\n");
        initRandomFile(filename, size);
    }

    printFileInformation(filename);

    int breakpoint = findBreakPoint(filename);
    printf("Breakpoint = %d", breakpoint);

    if (argc <= 1) {
        free(filename);
    }
}

void trim_file(const char *fileName, int position) {
    if (position < 0) return;

    FILE *file = fopen(fileName, "rb");
    if (!file) {
        printf("Error opening file for trimming.\n");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    int num, currentSize = 0;

    while (fread(&num, sizeof(int), 1, file) && currentSize <= position) {
        fwrite(&num, sizeof(int), 1, tempFile);
        currentSize++;
    }

    fclose(file);
    fclose(tempFile);

    if (remove(fileName) != 0) {
        printf("Error deleting original file.\n");
        return;
    }
    if (rename("temp.bin", fileName) != 0) {
        printf("Error renaming temporary file.\n");
        return;
    }
}

void task3(int argc, char *argv[]) {
    char *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Enter name of file: ");
        filename = initNameOfFile();
    }

    printf("Enter size: ");
    int size = getValidInput(1, 100);
    int choice;
    printf("Choose a method to fill the file:\n");
    printf("1. Fill file manually\n");
    printf("2. Fill file with random numbers\n");
    printf("Enter your choice (1 or 2): ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        printf("Initializing file with manual input:\n");
        initFileByHand(filename, size);
    } else if (choice == 2) {
        printf("Initializing file with random input:\n");
        initRandomFile(filename, size);
    }

    printFileInformation(filename);

    int breakpoint = findBreakPoint(filename);
    printf("Breakpoint = %d", breakpoint);

    trim_file(filename, breakpoint);
    printf("File after triming: \n");
    printFileInformation(filename);

    if (argc <= 1) {
        free(filename);
    }
}

void insertSorted(const char* filename, int value) {
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        printf("Error opening file for insertion.\n");
        return;
    }

    int num;
    long insertPos = 0;

    while (fread(&num, sizeof(int), 1, file)) {
        if (num > value) break;
        insertPos = ftell(file);
    }

    fseek(file, 0, SEEK_END);
    long endPos = ftell(file);
    while (endPos > insertPos) {
        fseek(file, -sizeof(int), SEEK_CUR);
        fread(&num, sizeof(int), 1, file);
        fseek(file, 0, SEEK_CUR);
        fwrite(&num, sizeof(int), 1, file);
        endPos -= sizeof(int);
        fseek(file, endPos, SEEK_SET);
    }

    fseek(file, insertPos, SEEK_SET);
    fwrite(&value, sizeof(int), 1, file);

    fclose(file);
}

void task4(int argc, char *argv[]) {
    char *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Enter name of file: ");
        filename = initNameOfFile();
    }

    printf("Enter size: ");
    int size = getValidInput(1, 100);
    int choice;
    printf("Choose a method to fill the file:\n");
    printf("1. Fill file manually\n");
    printf("2. Fill file with random numbers\n");
    printf("Enter your choice (1 or 2): ");
    choice = getValidInput(1, 2);

    if (choice == 1) {
        printf("Initializing file with manual input:\n");
        initFileByHand(filename, size);
    } else if (choice == 2) {
        printf("Initializing file with random input:\n");
        initRandomFile(filename, size);
    }

    printFileInformation(filename);

    printf("Enter numbers to insert in sorted order (non-number to stop):\n");
    int new_num;
    while (scanf("%d", &new_num) == 1) {
        insertSorted(filename, new_num);
        printFileInformation(filename);
    }

    if (argc <= 1) {
        free(filename);
    }
}