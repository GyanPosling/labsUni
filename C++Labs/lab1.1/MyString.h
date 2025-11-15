#pragma once
#include <iostream>
#include<string.h>

class MyString {
private:
    char* data;
    int length;

public:
    MyString() : data(nullptr), length(0) {}

    MyString(const char* str){
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    MyString(int size) : length(size) {
        data = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            data[i] = '\0';
        }
    }

    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    ~MyString() {
        delete[] data;
    }   

    MyString& operator=(const MyString& other);
    MyString intersectWith(const MyString& other) const;
    MyString operator&(const MyString& other) const;


    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);
};