#ifndef MYSTRING_H
#define MYSTRING_H

#pragma once
#include <iostream>

class Array{
private:
    int* data;
    int size;

public:
    Array();
    Array(int* array, int arraySize);
    Array(int size);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    Array& operator&(const Array& other);
    
    friend std::ostream& operator<<(std::ostream &os, const Array &array);
    friend std::istream& operator>>(std::istream &is, Array &array);
};

#endif 