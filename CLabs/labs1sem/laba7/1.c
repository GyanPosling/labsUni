#include <stdio.h>
#include <stdlib.h>

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

void printString(char *string) {
    printf("%s", string);
}

int countWordThatConsistOfEvenAmmountChar(char *string) {
    int count = 0;
    int charCount = 0;
    short inWord = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] != ' ' && string[i]!= '\n' && string[i] != '\t') {
            charCount++;
            inWord = 1;
        } else {
            if (inWord) {
                if (charCount % 2 == 0) {
                    count++;
                }
                charCount = 0;
                inWord = 0;
            }
        }
    }

    if (inWord && charCount % 2 == 0) {
        count++;
    }

   
    return count;
}


int main() {
    printf("Enter string: \n");
    char *string = getLine();
    printf("Your string: \n");
    printString(string);
    int count = countWordThatConsistOfEvenAmmountChar(string);
    printf("\ncount = %d", count);
    free(string);
    return 0;
}
