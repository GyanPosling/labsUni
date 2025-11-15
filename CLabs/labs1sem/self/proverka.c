#include<stdio.h>

// void check_size(int* value) {
//     while (1) {
//         char ch;
//         if (scanf_s("%c", &ch, 1) == 1 && ch != '\n' && ch != EOF) {
//             while (getchar() != '\n');
//             printf("Error!\nEnter again: ");
//         }
//         else {
//             break;
//         }
//     }
// }

void getValidInput(int* value) {
    while (1) {
        if (scanf("%d", value) == 1) {
            char ch;
            if ((ch = getchar()) == '\n' || ch == EOF) {
                break;
            } else {
                while (getchar() != '\n');
                printf("Error!\nTry again: ");
            }
        } else {
            while (getchar() != '\n');
            printf("Error!\nTry again: ");
        }
    }
}



int main(){
    int x;
    printf("Enter value: ");
    getValidInput(&x);
    printf("Value = %d", x);
    return 0;
}