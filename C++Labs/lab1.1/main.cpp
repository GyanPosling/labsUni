#include <iostream>
#include "MyString.h"
#include <string.h>
using namespace std;


void performIntersection() {
    int count;
    cout << "Enter number of strings: ";
    cin >> count;
    cin.ignore();
    
    MyString* strings = new MyString[count];
    for (int i = 0; i < count; i++) {
        cout << "String " << i + 1 << ": ";
        cin >> strings[i];
    }
    
    MyString result = strings[0];
    for (int i = 1; i < count; i++) {
        result = result & strings[i];
    }

    //result = result.intersectWith(strings[1].intersectWith(strings[2]));
    
    for (int i = 0; i < count; i++) {
        cout << strings[i];
        if (i < count - 1) cout << " & ";
    }
    cout << " = " << result << endl;
    
    delete[] strings;
}


void printRestartBox() {
    cout << "+------------------------------+\n";
    cout << "|   Restart? (1 = Yes, 0 = No) |\n";
    cout << "+------------------------------+\n";
    cout << "Answer: ";
}


int main() {
    int restart;
    
    do {
        performIntersection();
        printRestartBox();
        cin >> restart;
    } while (restart == 1);

    cout<<"Exiting...";
    
    return 0;
}
