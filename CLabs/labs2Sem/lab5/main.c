#include "validators.h"
#include "stacksImplement.h"
#include "sumTask.h"
#include "mergeTask.h"
#include "rpnTask.h"

void displayMenu() {
    printf("\n============ Menu ============\n");
    printf("1. Sum Task (Calculate sum of stack elements)\n");
    printf("2. Merge Task (Merge two sorted stacks)\n");
    printf("3. RPN Task (Polish notation calculator)\n");
    printf("4. Exit\n");
    printf("==============================\n");
    printf("Enter your choice (1-4): ");
}


int main() {
    int choice;
    
    do {
        displayMenu();
        choice = getValidInput(1, 4);
        
        switch(choice) {
            case 1:
                printf("\n=== Sum Task ===\n");
                sumTask();
                break;
            case 2:
                printf("\n=== Merge Task ===\n");
                mergeTask();
                break;
            case 3:
                printf("\n=== RPN Task ===\n");
                rpnTask();
                break;
            case 4:
                printf("\nExiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        if (choice != 4) {
            printf("\nPress Enter to continue...");
            rewind(stdin);
            getchar();
        }
    } while (choice != 4);

    return 0;
}

//gcc validators.c sumTask.c mergeTask.c rpnTask.c stacksImplement.c main.c -o main.exe