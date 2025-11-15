#pragma once
#include <iostream>
#include <cstring>

class String {
private:
    char* data;
    int length;

public:
    String() : data(nullptr), length(0) {}                              // Конструктор по умолчанию

    String(const char* str) {                                           // Конструктор с параметорм(Строка)
        this->length = strlen(str);
        this->data = new char[this->length + 1];
        strcpy(this->data, str);
    }

    String(int size) : length(size) {                                   // Конструктор с параметорм(размер)
        this->data = new char[this->length + 1];
        for (int i = 0; i <= this->length; i++) {
            this->data[i] = '\0';
        }
    }

    String(const String& other) {                                         // Конструктор копирования
        this->length = other.length;
        this->data = new char[this->length + 1];
        strcpy(this->data, other.data);
    }

    ~String() {                                                            // Деструктор
        delete[] this->data;
    }

    String& operator=(const String& other);                                // Переопределения присваивания

    String operator+(const String& other) const;                           // Объект + Объект
    String operator+(const char* str) const;                               // Объект + Строка
    friend String operator+(const char* str, const String& obj);           // Строка + Объект
    String operator-(const String& other) const;                           // Объект - Объект
    String operator-(const char* string) const;                            // Объект - Строка
    friend String operator-(const char* string, const String& object);     // Строка - Объект

    String& operator+=(const String& other);                               // Объект += Объект
    String& operator+=(const char *string);                                // Объект += Строка
    String& operator-=(const String& other);                               // Объект -= Объект
    String& operator-=(const char* string);                                // Объект -= Строка

    String operator*(int multiplyDigit) const;                             // Объект * число (умножение строки)
    String& operator*=(int multiplyDigit);                                 // Объект *= число

    char& operator[](int index);                                           // доступ по индексу (неконстантный)
    const char& operator[](int index) const;                               // доступ по индексу (константный)

    String operator()(int start, int end) const;                           // получение подстроки

    short operator>(const String& other) const;                            // сравнение > (по длине)
    short operator<(const String& other) const;                            // сравнение < (по длине)
    short operator==(const String& other) const;                           // сравнение == (по содержимому)
    short operator!=(const String& other) const;                           // сравнение != (по содержимому)
    short operator<=(const String& other) const;                           // сравнение <= (по длине)
    short operator>=(const String& other) const;                           // сравнение >= (по длине)

    String operator&(const String& other) const;                           // пересечение Объектов
    String operator&(const char* string) const;                            // пересечение Объекта и строки
    friend String operator&(const char* string, String& object);           // пересечение строки и Объекта

    String& operator++();                                                  // префиксный инкремент
    String operator++(int);                                                // постфиксный инкремент
    String& operator--();                                                  // префиксный декремент
    String operator--(int);                                                // постфиксный декремент

    friend std::ostream& operator<<(std::ostream& os, const String& obj);  // вывод в поток
    friend std::istream& operator>>(std::istream& is, String& obj);        // ввод из потока

};