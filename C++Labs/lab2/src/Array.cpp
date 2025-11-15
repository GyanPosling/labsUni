#include "Array.h"
using namespace std;

Array::Array() : data(nullptr), size(0) {}

Array::Array(int* array, int arraySize) {
    size = arraySize;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = array[i];
    }
}

Array::Array(int size) : size(size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

Array::Array(const Array& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        data = new int[size];
        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

Array::~Array() {
    delete[] data;
}

Array& Array::operator&(const Array& other) {
    Array tempArray((this->size < other.size) ? this->size : other.size);

    int resultSize = 0;
    
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < other.size; j++) {
            if (this->data[i] == other.data[j]) {
                bool duplicate = false;
                for (int k = 0; k < resultSize; k++) {
                    if (tempArray.data[k] == this->data[i]) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    tempArray.data[resultSize++] = this->data[i];
                }
                break;
            }
        }
    }
    
    Array resultArray(resultSize);
    for (int i = 0; i < resultSize; i++) {
        resultArray.data[i] = tempArray.data[i];
    }

    *this = resultArray;
    return *this;

}

std::ostream& operator<<(std::ostream &os, const Array &array){
    os<<"[";

    for(int i = 0; i < array.size; i++){
        os<< array.data[i];
        if(i < array.size - 1){
            os<<", ";
        }
    }

    os<<"]";

    return os;
}

std::istream& operator>>(std::istream &is, Array &array){
    int newSize;
    std::cout<<"Enter size: ";
    is>>newSize;

    if (newSize <= 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    delete [] array.data;

    array.size = newSize;
    array.data = new int[array.size];

    for(int i = 0; i < array.size; i++){
        std::cout<<"Enter "<< i + 1<< " element: ";
        is>>array.data[i];
    }

    return is;
}

