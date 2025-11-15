#include "validators.h"
#include <stdio.h>
#include "tree_lobby.h"
#include <unistd.h>

int main(void)
{
    int running = 1;
    while(running != 2) {
       clearScreen();
        printf("\n+=============================================+\n");
        printf("|         Binary Tree Operations             |\n");
        printf("+=============================================+\n");
        printf("| 1 - Start working with tree                |\n");
        printf("| 2 - Exit                                   |\n");
        printf("+=============================================+\n");
        printf("-> ");

        int choice = execute_verification(1, 3);
        running = tree_work_menu(choice);
    }
}