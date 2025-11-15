#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

// Общие функции
int getValidInput(int min, int max);
char* initNameOfFile();
void initFileByHand(const char* filename, int size);
void initRandomFile(const char* filename, int size);
void printFileInformation(const char *fileName);
void swap(int* a, int* b);

// Функции для задачи 1
void task1(int argc, char *argv[]);

// Функции для задачи 2
int findBreakPoint(char *fileName);
void task2(int argc, char *argv[]);

// Функции для задачи 3
void trim_file(const char *fileName, int position);
void task3(int argc, char *argv[]);

// Функции для задачи 4
void insertSorted(const char* filename, int value);
void task4(int argc, char *argv[]);

#endif