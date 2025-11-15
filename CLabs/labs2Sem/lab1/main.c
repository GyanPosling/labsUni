#include "func.h"

void displayMenu() {
    printf("\n=== Main Menu ===\n");
    printf("1. Task 1 - Basic File Operations\n");
    printf("2. Task 2 - Find Break Point\n");
    printf("3. Task 3 - Trim File\n");
    printf("4. Task 4 - Insert Sorted\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
}

int main(int argc, char *argv[]) {
    int choice;
    
    do {
        displayMenu();
        choice = getValidInput(1, 5);
        
        switch(choice) {
            case 1:
                task1(argc, argv);
                break;
            case 2:
                task2(argc, argv);
                break;
            case 3:
                task3(argc, argv);
                break;
            case 4:
                task4(argc, argv);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    
    return 0;
}