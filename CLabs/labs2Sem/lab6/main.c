#include <stdio.h>
#include "queueTask.h"
#include "deque.h"
#include "dequeCompareTask.h"
#include "validators.h"


// задание 1:
// Создать очередь для целых (положительных и отрицательных) чисел. Максимальный размер
// очереди вводится с экрана. Создать функции для ввода, вывода и определения размера очереди. Ввести
// 6 элементов. Вывести элементы очереди до первого отрицательного (включительно). Вывести размер
// оставшейся очереди.
// задание 2:
// Создать дек для целых (положительных и отрицательных) чисел. Максимальный размер дека
// вводится с экрана. Создать функции для ввода, вывода и определения размера дека. Ввести 3 элемента
// справа и 3 слева. Вывести элементы дека справа до первого отрицательного (включительно). Вывести
// размер оставшегося дека.
// задание 3:
// Найдите среди трех (4, 5) очередей две одинаковые. Решение в программе оформляйте через
// подпрограммы.

// Бурш Антон 458302
// вариант - 4

void printMenu() {
    printf("\n=================================\n");
    printf("-------------- Menu ---------------\n");
    printf("1. Task 1 (Queue operations)\n");
    printf("2. Task 2 (Deque operations)\n");
    printf("3. Task 3 (Find identical queues)\n");
    printf("4. Exit\n");
    printf("====================================\n");
    printf("Select option: ");
}

int main(void) {
    int choice;
    do {
        printMenu();
        choice = getValidInput(1, 4);

        switch (choice) {
            case 1:
                printf("\n===== TASK 1 START ========\n");
                runQueue();
                printf("\n=====TASK 1 END ======\n");
                break;
            case 2:
                printf("\n========= TASK 2 START ==========\n");
                runDeque();
                printf("\n======== TASK 2 END ===========\n");
                break;
            case 3:
                printf("\n========= TASK 3 START =========\n");
                findSameQueue();
                printf("\n========= TASK 3 END =============\n");
                break;
        }
    } while(choice != 4);

    return 0;
}