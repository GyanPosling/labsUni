#include "func.h"

int main() {
    char filename[256];
    name_of_file(filename);
    write_file(filename);
    read_file(filename);
    
    char choice;
    do {
        printMenu();
        printf("Select option: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                write_file(filename);
                read_file(filename);
                break;
            case '2': {
                char c;
                printf("Enter character: ");
                scanf(" %c", &c);
                int count = count_char(filename, c);
                printf("Count: %d\n", count);
                break;
            }
            case '3': {
                printf("Start index: ");
                int start = get_valid_index(filename);
                if(start == -1) break;
                
                printf("End index: ");
                int end = get_valid_index(filename);
                if(end == -1) break;
                
                reverse_substring(filename, start, end);
                read_file(filename);
                break;
            }
            case '4':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option\n");
        }
        
        if(choice != '4') {
            printf("Continue? (1-Yes, 0-No): ");
            scanf(" %c", &choice);
        }
    } while(choice == '1' && choice != '4');
    
    return 0;
}