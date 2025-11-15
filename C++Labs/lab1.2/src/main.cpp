#include "../include/String.hpp"
#include <limits>
#include <iostream>

using namespace std;

void testAdditionOperators() {
    cout << "======= Testing operator '+' =========" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    const char* constString = {"const string"};
    
    String result1 = s1 + s2;
    cout << "object + object = " << result1 << endl;
    
    result1 = s1 + constString;
    cout << "object(s1) + const String('const string') = " << result1 << endl;
    
    result1 = constString + s2;
    cout << "const String('const string') + object(s2) = " << result1 << endl;

}

void testPlusEqualsOperator() {
    cout << "======== Testing operator '+=' ===============" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    
    String s3 = s1;
    s3 += s2;
    cout << "s1 += s2: " << s3 << endl;
}

void testDifferenceOperators() {
    cout << "======= Testing operator '-' =========" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    const char* constString = {"const string"};
    
    String result1 = s1 - s2;
    cout << "object - object = " << result1 << endl;
    
    result1 = s1 - constString;
    cout << "object(s1) - const String('const string') = " << result1 << endl;
    
    result1 = constString - s2;
    cout << "const String('const string') - object(s2) = " << result1 << endl;

}

void testDifferenceEqualsOperator() {
    cout << "======== Testing operator '-=' ===============" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    
    String s3 = s1;
    s3 -= s2;
    cout << "s1 -= s2: " << s3 << endl;
}

void testMultiplyOperators() {
    cout << "======= Testing operator '*' =========" << endl;
    String s;
    cin >> s;
    int multiplyDigit;
    cout << "Enter digit on which u wana multyply: ";
    cin >> multiplyDigit;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    String result = s * multiplyDigit;
    cout << "object * digit = " << result << endl;
}


void testMultiplyEqualsOperator() {
    cout << "======== Testing operator '*=' ===============" << endl;
    String s;
    cin >> s;
    int multiplyDigit;
    cout << "Enter digit on which u wana multyply: ";
    cin >> multiplyDigit;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    
    s *= multiplyDigit;
    cout << "object *= digit: " << s << endl;
}

void testIntersection(){
    cout << "======== Testing operator '&' ===============" << endl;
    String s1, s2;
    cin>>s1>>s2;
    String result = s1 & s2;
    cout<<"Result = "<< result<<endl;
}

void testIndexOperator() {
    cout << "======= Testing operator '[]' ========" << endl;
    String s;
    cin >> s;
    
    int index;
    cout << "Enter index: ";
    cin >> index;
    cout << "Char in " << index << " position = " << s[index] << endl;
    cin.ignore();
}

void testSubstringOperator() {
    cout << "======= Testing operator '()' substring ========" << endl;
    String s;
    cin >> s;
    
    int start, end;
    cout << "Enter start and end indices for substring: ";
    cin >> start >> end;
    cin.ignore();
    String subString = s(start, end);
    cout << "Substring (start = " << start << ", end = " << end << ") = " << subString << endl;
}

void testComparisonOperators() {
    cout << "======= Testing comparison operators ========" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    
    cout << "s1 = " << s1 << ", s2 = " << s2 << endl;
    cout << "s1 == s2: " << (s1 == s2) << endl;
    cout << "s1 != s2: " << (s1 != s2) << endl;
    cout << "s1 > s2: " << (s1 > s2) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;
    cout << "s1 >= s2: " << (s1 >= s2) << endl;
    cout << "s1 <= s2: " << (s1 <= s2) << endl;
}

void testIncrementDecrementOperators() {
    cout << "======= Testing increment/decrement operators ========" << endl;
    String s5 = "abc";
    cout << "Original string: " << s5 << endl;

    ++s5;
    cout << "After prefix ++: " << s5 << endl;
    
    --s5;
    cout << "After prefix --: " << s5 << endl;

    cout <<"Exiting... ";
}

void checkAllOperationInLine(){
    cout << "Check all operations in line";
    String s1, s2;
    cin >> s1 >> s2;
    
    String result = (s1 > s2 ? ++s1 + " is greater" + (s1 += "!") : --s2 + " is smaller" + (s2 += "?")) + (s1[0] == s2[0] ? " same_start" : " diff_start") + (s1(0,2) + s2(0,2)) + (s1 += s2 += " end");
    cout << result << endl;

    // String result;
    // if (s1 > s2) {
    //     ++s1;
    //     result = s1 + " is greater" + (s1 += "!");
    // } else {
    //     --s2;
    //     result = s2 + " is smaller" + (s2 += "?");
    // }

    // if (s1[0] == s2[0]) {
    //     result += " same_start";
    // } else {
    //     result += " diff_start";
    // }

    // result += s1(0, 2) + s2(0, 2);
    // s2 += " end";
    // s1 += s2;
    // result += s1;

    // cout << result << endl;
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
        testAdditionOperators();
        testPlusEqualsOperator();
        testDifferenceOperators();
        testDifferenceEqualsOperator();
        //testMultiplyOperators();
        //testMultiplyEqualsOperator();
        testIntersection();
        testIndexOperator();
        testSubstringOperator();
        testComparisonOperators();
        testIncrementDecrementOperators();
        checkAllOperationInLine();
        printRestartBox();
        cin >> restart;
    } while (restart == 1);

    cout<<"Exiting...";

    return 0;
}