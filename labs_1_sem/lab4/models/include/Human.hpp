#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum SearchMode { FULL_MATCH, LAST_NAME, FIRST_NAME, MIDDLE_NAME, BIRTH_YEAR };

class Human {
protected:
    string firstName;
    string lastName;
    string middleName;
    int birthYear;
private:
    static SearchMode currentSearchMode;
public:
    Human();
    Human(const string& first, const string& last, const string& middle, int year);
    virtual ~Human();
    
    Human& operator=(const Human& other);
    bool operator==(const Human& other) const;
    bool operator<(const Human& other) const;
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
    static void setSearchMode(SearchMode mode);

    virtual void printHeader() const = 0;
    virtual void printTable() const = 0;
};