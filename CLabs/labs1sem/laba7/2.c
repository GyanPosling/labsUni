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

int stringLength(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


int findThePositionOfSubstring(char *s, char *s0) {
    int position = -1;
    int mainLength = stringLength(s);
    int sudLength = stringLength(s0);
    for (int i = 0; i <= mainLength - sudLength; i++) {
        int j = 0;
        while (j < sudLength && s[i + j] == s0[j]) {
            j++;
        }
        if (j == sudLength) {
            position = i;
            break;
        }
    }
    return position;
}

int main() {
    printf("\nEnter the main string: \n");
    char*S = getLine(); 
    printf("\nEnter the substring: \n");
    char*S0 = getLine();
  
    printf("\nYour main string:\n");
    printString(S);
    printf("\nYour substring:\n");
    printString(S0);

    int position = findThePositionOfSubstring(S, S0);
    printf("\nPosition of substring in main string = %d", position);

    free(S);
    free(S0);
    return 0;
}
