#include "MyString.h"
#include <cstring>
using namespace std;

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}

MyString MyString::intersectWith(const MyString& other) const{

    MyString resultString((this->length < other.length) ? this->length : other.length);
    
    int resultLength = 0;
    
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < other.length; j++) {
            if (this->data[i] == other.data[j]) {
                short duplicate = 0;
                for (int k = 0; k < resultLength; k++) {
                    if (resultString.data[k] == this->data[i]) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    resultString.data[resultLength] = this->data[i];
                    resultLength++;
                }
                break;
            }
        }
    }
    
    resultString.data[resultLength] = '\0';
    resultString.length = resultLength;

    // *this = resultString;
    return resultString;

}

MyString MyString::operator&(const MyString& other) const{
    return this->intersectWith(other);
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    if (str.data != nullptr) {
        os <<"'"<< str.data<< "'";
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char ch;
    int capacity = 10;
    int size = 0;
    char* buffer = new char[capacity];
    
    while (is.get(ch) && ch != '\n') {
        if (size >= capacity - 1) {
            capacity *= 2;
            char* newBuffer = new char[capacity];
            strcpy(newBuffer, buffer);
            delete[] buffer;
            buffer = newBuffer;
        }
        buffer[size++] = ch;
    }
    buffer[size] = '\0';
    
    delete[] str.data;
    str.length = size;
    str.data = new char[str.length + 1];
    strcpy(str.data, buffer);
    
    delete[] buffer;
    return is;
}

