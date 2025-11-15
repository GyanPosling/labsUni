#include "1task.h"
#include"validators.h"

void printHigherBits(char num) {
    BitField bitField;
    bitField.high_bits = (num >> 4) & 0x0F;
    printf("Upper 4 bits: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (bitField.high_bits >> i) & 1); 
    }
    printf("\n");
}

void findFourBits() {
    char num = getValidCharInteger(-128, 127); 
    printHigherBits(num); 
}