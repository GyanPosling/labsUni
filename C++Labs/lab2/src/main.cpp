#include <iostream>
#include "Array.h"

using namespace std;

void performIntersection() {
    int count;
    cout << "Enter number of arrays: ";
    cin >> count;
    cin.ignore();
    
    Array* arrays = new Array[count];
    for (int i = 0; i < count; i++) {
        cin>>arrays[i];
    }
    
    Array result = arrays[0];
    for (int i = 1; i < count; i++) {
        result = result & arrays[i];
    }
    
    cout << "Intersection: ";
    for (int i = 0; i < count; i++) {
        cout << arrays[i];
        if (i < count - 1) {
            cout << " & ";
        }
    }
    cout << " = " << result << endl;
    
    delete[] arrays;
}

void printRestartBox() {
    cout << "+------------------------------+\n";
    cout << "|   Restart? (1 = Yes, 0 = No) |\n";
    cout << "+------------------------------+\n";
    cout << "Answer: ";
}

int main() {
    int restart = 1;
    
    do {
        performIntersection();
        printRestartBox();
        cin >> restart;
        cin.ignore();
    } while (restart == 1);

    cout << "Exiting...";
    
    return 0;
}