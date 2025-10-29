#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include<string>
using namespace std;

class Human {
protected:
    string firstName;
    string lastName;
    string middleName;
    int birthYear;
public:
    Human();
    Human(const string& first, const string& last, const string& middle, int year);
    virtual ~Human();
    
    Human& operator=(const Human& other);
    friend ostream& operator<<(ostream& os, const Human& human);
    friend istream& operator>>(istream& is, Human& human);
    
    string getFirstName() const;
    string getLastName() const;
    string getMiddleName() const;
    int getBirthYear() const;
    
    void setFirstName(const string& first);
    void setLastName(const string& last);
    void setMiddleName(const string& middle);
    void setBirthYear(int year);
    
    virtual void printHeader() const = 0;
    virtual void printTable() const = 0;
};