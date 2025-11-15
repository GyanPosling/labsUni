#include "validators.h"

int execute_verification(int min_limit, int max_limit)
{
    char input[100];
    int number;
    char symbol;

    while(1)
    {
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error! Try again!\n");
            continue;
        }

        if (sscanf(input, "%d %c", &number, &symbol) != 1)
        {
            printf("Input error! Enter integer:\n");
            continue;
        }

        if (number > max_limit || number < min_limit)
        {
            printf("Input error! Enter number in range [%d, %d]:\n", min_limit, max_limit);
            continue;
        }

        return number;
    }
}

void clearScreen()
{
    printf("\033c");
    fflush(stdout);
}
