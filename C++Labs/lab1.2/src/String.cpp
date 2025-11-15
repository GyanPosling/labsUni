#include "../include/String.hpp"
#include <cstring>

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}

String String::operator+(const String& other) const{
    String resultString(this->length + other.length);
    strcpy(resultString.data, this->data);
    strcat(resultString.data, other.data);
    return resultString;
}

String String::operator+(const char* string) const{
    return *this + String(string);
}

String operator+(const char* string, const String& object) {
    return String(string) + object;
}

String& String::operator+=(const String& other) {
    *this = *this + other;
    return *this;
}

String& String::operator+=(const char* string) {
    *this = *this + string;
    return *this;
}

String String::operator-(const String& other) const{
    String resultString(this->length);
    int resultLength = 0;
    
    for (int i = 0; i < this->length; i++) {
        short found = 0;
        for (int j = 0; j < other.length; j++) {
            if (this->data[i] == other.data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            resultString.data[resultLength] = this->data[i];
            resultLength++;
        }
    }
    
    resultString.data[resultLength] = '\0';
    resultString.length = resultLength;
    return resultString;
}

String String::operator-(const char* string) const{
    return *this - String(string);
}

String operator-(const char* string, const String& object) {
    return String(string) - object;
}

String& String::operator-=(const String& other) {
    *this = *this - other;
    return *this;
}

String& String::operator-=(const char* string) {
    *this = *this - string;
    return *this;
}

String String::operator*(int multiplyDigit) const{
    if (multiplyDigit <= 0) return String();
    
    String result;
    for(int i = 0; i < multiplyDigit; i++){
        result = result + *this;
    }
    return result;
}

String& String::operator*=(int multiplyDigit){
    *this = *this * multiplyDigit;
    return *this;
}

String String::operator&(const String& other)const{
    String resultString((this->length < other.length) ? this->length : other.length);
    
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

    return resultString;
}

String String::operator&(const char* string)const{
    String result = *this & String(string);
    return result;
}

String operator&(const char* string, String& object){
    String result = String(string) & object;
    return result;
}

char& String::operator[](int index) {
    char nullChar = '\0';
    return (index >= 0 && index < length) ? data[index] : nullChar;
}


String String::operator()(int start, int end) const {
    if (start < 0 || end >= length || start > end) {
        return String();
    }
    String result(end - start + 1);
    for (int i = 0; i < end - start + 1; i++) {
        result.data[i] = this->data[start + i];
    }
    result.data[end - start + 1] = '\0';
    return result;
}

short String::operator>(const String& other) const {
    return this->length > other.length;
}

short String::operator<(const String& other) const {
    return this->length < other.length;
}

short String::operator==(const String& other) const {
    return strcmp(this->data, other.data) == 0;
}

short String::operator!=(const String& other) const {
    return !(*this == other);
}

short String::operator>=(const String& other) const {
    return this->length >= other.length;
}

short String::operator<=(const String& other) const {
    return this->length <= other.length;
}

String& String::operator++() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] + 1;
        }
    }
    return *this;
}

String String::operator++(int) {
    String temp(*this);
    ++(*this);
    return temp;
}

String& String::operator--() {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] != '\0') {
            this->data[i] = this->data[i] - 1;
        }
    }
    return *this;
}

String String::operator--(int) {
    String temp(*this);
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
    if (string.data != nullptr) {
        os << "'" << string.data << "'";
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& string) {
    char buffer[80];
    std::cout << "Enter string: ";
    is.getline(buffer, 80);
    string = String(buffer);
    return is;
}