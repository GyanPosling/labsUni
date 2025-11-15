#include "default_tree.h"
#include "tree_functions.h"
#include <time.h>

Node* create_tree_manually()
{
    Node* root = NULL;
    printf("\n+--------------------------------------------+\n");
    printf("| Enter number of tree elements:             |\n");
    printf("+--------------------------------------------+\n");
    printf("-> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        printf("\n+------------------------------+\n");
        printf("| Enter element value:         |\n");
        printf("+------------------------------+\n");
        printf("-> ");
        int value = execute_verification(min_limit, max_limit);
        root = insert(root, value);
    }
    printf("\n+--------------------------------+\n");
    printf("| Tree created successfully!     |\n");
    printf("+--------------------------------+\n");
    return root;
}

Node* create_tree_hand_rand()
{
    Node* root = NULL;
    printf("\n+--------------------------------------------+\n");
    printf("| Enter number of tree elements:             |\n");
    printf("+--------------------------------------------+\n");
    printf("-> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        int value = rand() % (100 - 0 + 1) + 0;
        root = insert(root, value);
    }
    printf("\n+--------------------------------+\n");
    printf("| Tree created successfully!     |\n");
    printf("+--------------------------------+\n");
    return root;
}

Node* create_tree_rand()
{
    Node* root = NULL;
    int count = rand() % (30 - 5 + 1) + 5;
    for(int i = 0; i < count; i++)
    {
        int value = rand() % (100 - 0 + 1) + 0;
        root = insert(root, value);
    }
    printf("\n+--------------------------------+\n");
    printf("| Tree created successfully!     |\n");
    printf("+--------------------------------+\n");
    return root;
}

void output_menu(Node* root)
{
    printf("\n+--------------------------------------------+\n");
    printf("| Select output method:                     |\n");
    printf("| 1 - Ascending order                      |\n");
    printf("| 2 - Descending order                     |\n");
    printf("| 3 - Tree structure                       |\n");
    printf("+--------------------------------------------+\n");
    printf("-> ");

    int choice = execute_verification(1, 3);
    switch(choice)
    {
        case 1:
            printf("\n+------------------------------------+\n");
            printf("| Tree in ascending order:           |\n");
            printf("+------------------------------------+\n");
            in_order_show(root);
            break;

        case 2:
            printf("\n+------------------------------------+\n");
            printf("| Tree in descending order:          |\n");
            printf("+------------------------------------+\n");
            reversed_in_order_show(root);
            break;

        case 3:
            printf("\n+----------------------------+\n");
            printf("| Tree structure:            |\n");
            printf("+----------------------------+\n");
            as_tree_print(root, 0, 0);
    }
    printf("\n");
}

void default_tree_actions(Node* root)
{
    clearScreen();
    int running = 1;
    int value;

    while(running) {
        printf("\n+----------------------------------------------------------+\n");
        printf("| Select action:                                            |\n");
        printf("| 0 - Tree size                                             |\n");
        printf("| 1 - Recreate tree                                         |\n");
        printf("| 2 - View tree contents                                    |\n");
        printf("| 3 - Add element                                           |\n");
        printf("| 4 - Delete element                                        |\n");
        printf("| 5 - Search element                                        |\n");
        printf("| 6 - Find max duplicates                                   |\n");
        printf("| 8 - Balance tree                                          |\n");
        printf("| 9 - Clear tree                                            |\n");
        printf("| 10 - Exit to main menu                                    |\n");
        printf("+----------------------------------------------------------+\n");
        printf("-> ");

        int user_choice = execute_verification(0, 10);

        switch (user_choice)
        {
            case 0:
                if(root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                    break;
                }
                int size = 0;
                get_tree_size(root, &size);
                printf("\n+------------------------------------+\n");
                printf("| Tree size: %3d                   |\n", size);
                printf("+------------------------------------+\n");
                break;

            case 1:
                default_tree_menu();
                return;

            case 2:
                if(root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                    break;
                }
                output_menu(root);
                break;

            case 3:
                printf("\n+----------------------------------+\n");
                printf("| Enter value to add:             |\n");
                printf("+----------------------------------+\n");
                printf("-> ");
                value = execute_verification(min_limit, max_limit);
                root = insert(root, value);
                printf("\n+--------------------------------------+\n");
                printf("| Value %3d added successfully!       |\n", value);
                printf("+--------------------------------------+\n");
                break;

            case 4:
                if(root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                    break;
                }
                printf("\n+--------------------------------------------+\n");
                printf("| Enter value to delete:                    |\n");
                printf("+--------------------------------------------+\n");
                printf("-> ");
                value = execute_verification(min_limit, max_limit);
                Node* found = search_node(root, value);
                if(found != NULL) {
                    printf("\n+--------------------------------------+\n");
                    printf("| Element %3d deleted successfully!   |\n", value);
                    printf("+--------------------------------------+\n");
                }
                else {
                    printf("\n+--------------------------------------+\n");
                    printf("| Element %3d not found!              |\n", value);
                    printf("+--------------------------------------+\n");
                }
                root = delete(root, value);
                break;

            case 5:
                if(root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                    break;
                }
                printf("\n+------------------------------------+\n");
                printf("| Enter value to search:            |\n");
                printf("+------------------------------------+\n");
                printf("-> ");
                value = execute_verification(min_limit, max_limit);
                Node* temp = search_node(root, value);
                if(temp != NULL) {
                    printf("\n+--------------------------------------+\n");
                    printf("| Element %3d found!                 |\n", value);
                    printf("+--------------------------------------+\n");
                }
                else {
                    printf("\n+--------------------------------------+\n");
                    printf("| Element %3d not found!             |\n", value);
                    printf("+--------------------------------------+\n");
                }
                break;

            case 6:
                if(root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                    break;
                }
                find_repeats(root);
                break;

            case 7:
                if(root == NULL) {
                    printf("\n+--------------------------------------------+\n");
                    printf("|    Tree already cleared!                |\n");
                    printf("+--------------------------------------------+\n");
                    break;
                }
                clean_tree(root);
                printf("\n+--------------------------------+\n");
                printf("|     Tree cleared successfully   |\n");
                printf("+--------------------------------+\n");
                root = NULL;
                break;

            case 8:
                if (root == NULL) {
                    printf("\n+----------------------------+\n");
                    printf("|      Tree is empty...      |\n");
                    printf("+----------------------------+\n");
                } else {
                    root = balance_tree(root);
                    printf("\n+---------------------------------------+\n");
                    printf("| Tree has been balanced successfully! |\n");
                    printf("+---------------------------------------+\n");
                }
                break;
            case 9:
                printf("\n+----------------------------+\n");
                printf("| Returning to main menu... |\n");
                printf("+----------------------------+\n");
                running = 0;
                break;
        }
    }
}

void default_tree_menu()
{
    clearScreen();
    srand(time(NULL));
    Node* root = NULL;
    char user_choice[50];
    printf("\n+----------------------------------------------------------+\n");
    printf("| Select tree creation method:                           |\n");
    printf("| 1 - Manual creation                                    |\n");
    printf("| 2 - Random with size                                  |\n");
    printf("| Other key - Full random                               |\n");
    printf("+----------------------------------------------------------+\n");
    printf("-> ");
    fgets(user_choice, 50, stdin);

    switch (user_choice[0])
    {
        case '1':
            root = create_tree_manually();
            break;

        case '2':
            root = create_tree_hand_rand();
            break;

        default:
            root = create_tree_rand();
    }

    default_tree_actions(root);
}