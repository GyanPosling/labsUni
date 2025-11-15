// 1. Для целого числа (char) вывести его старшие 4 бита в двоичной системе
// счисления.
// 2. Структура содержит информацию о вакансиях: оклад (число), название
// (указатель), вложенную структуру – дополнительные требования (строка
// фиксированной длины) и требуемый стаж работы. Найти вакансии с
// заданным окладом. Удалить вакансии с названием короче заданной длины.

// gcc 1task.c vacancySystem.c validators.c main.c -o main.exe

//Бурш Антон Павлович
//15.03.2025


#include "1task.h"
#include"vacancySystem.h"
#include"validators.h"

int main(){
    printf("What task needs to be run?\nEnter: ");
    int choise = getValidInput(1, 2);
    if(choise == 1)
        findFourBits();
    else
        runStorage();

    return 0;
}