#include "func.h"

void printMenu() {
    printf("\n");
    printf("+-----------------------------------+\n");
    printf("|          FILE OPERATIONS MENU     |\n");
    printf("+-----------------------------------+\n");
    printf("| 1. Rewrite file & view contents   |\n");
    printf("| 2. Count character occurrences    |\n");
    printf("| 3. Reverse substring in file      |\n");
    printf("| 4. Exit program                   |\n");
    printf("+-----------------------------------+\n");
}

void name_of_file(char* filename) {
    printf("Enter filename: ");
    scanf("%255s", filename);
    if(strstr(filename, ".txt") == NULL) {
        strcat(filename, ".txt");
    }
}

void write_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if(!file) return;
    
    printf("Enter text: ");
    getchar();
    char c;
    while((c = getchar()) != '\n' && c != EOF) {
        fputc(c, file);
    }
    fclose(file);
}

void read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(!file) return;
    
    printf("\nFile contents: ");
    char ch;
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(file);
}

int count_char(const char* filename, char c) {
    FILE* file = fopen(filename, "r");
    if(!file) return 0;
    
    int count = 0;
    char ch;
    while((ch = fgetc(file)) != EOF) {
        if(ch == c) count++;
    }
    fclose(file);
    return count;
}

int get_file_size(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(!file) return -1;
    
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);
    return size;
}

int get_valid_index(const char* filename) {
    int size = get_file_size(filename);
    int index;
    scanf("%d", &index);
    
    if(index < 0 || index >= size) {
        printf("Invalid index\n");
        return -1;
    }
    return index;
}

void reverse_substring(const char* filename, int index1, int index2) {
    FILE* file = fopen(filename, "r+");
    if(!file) return;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    if(index1 < 0 || index2 < 0 || index1 >= fileSize || index2 >= fileSize) {
        fclose(file);
        printf("Invalid indices\n");
        return;
    }

    if(index1 < index2) {
        for(int i = 0; i < (index2 - index1 + 1) / 2; i++) {
            fseek(file, index1 + i, SEEK_SET);
            char tmp1;
            fread(&tmp1, 1, 1, file);

            fseek(file, index2 - i, SEEK_SET);
            char tmp2;
            fread(&tmp2, 1, 1, file);

            fseek(file, index1 + i, SEEK_SET);
            fwrite(&tmp2, 1, 1, file);

            fseek(file, index2 - i, SEEK_SET);
            fwrite(&tmp1, 1, 1, file);
        }
    }
    else {
        for(int i = 0; i < (index1 - index2 + 1) / 2; i++) {
            fseek(file, index2 + i, SEEK_SET);
            char tmp1;
            fread(&tmp1, 1, 1, file);

            fseek(file, index1 - i, SEEK_SET);
            char tmp2;
            fread(&tmp2, 1, 1, file);

            fseek(file, index2 + i, SEEK_SET);
            fwrite(&tmp2, 1, 1, file);

            fseek(file, index1 - i, SEEK_SET);
            fwrite(&tmp1, 1, 1, file);
        }
    }
    fclose(file);
}