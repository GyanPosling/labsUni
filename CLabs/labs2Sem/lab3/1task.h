#ifndef TASK1_H
#define TASK1_H

#include <stdio.h>

typedef struct {
    unsigned int high_bits : 4;
} BitField;

void printHigherBits(char num);
void findFourBits();

#endif