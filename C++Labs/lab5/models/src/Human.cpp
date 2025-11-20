#include "../include/Human.hpp"
#include "../../exceptions/include/InputHandler.hpp"
using namespace std;

Human::Human() : birthday() {}

Human::Human(const string& first, const string& last, const string& middle, const Date& birth)
    : firstName(first), lastName(last), middleName(middle), birthday(birth) {}

Human::~Human() {}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->middleName = other.middleName;
        this->birthday = other.birthday;
    }
    return *this;
}

bool Human::operator==(const Human& other) const {
    if (currentSearchMode == FULL_MATCH) {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               middleName == other.middleName &&
               birthday == other.birthday;
    } else if (currentSearchMode == LAST_NAME) {
        return lastName == other.lastName;
    } else if (currentSearchMode == FIRST_NAME) {
        return firstName == other.firstName;
    } else if (currentSearchMode == MIDDLE_NAME) {
        return middleName == other.middleName;
    } else if (currentSearchMode == BIRTH_YEAR) {
        return birthday == other.birthday;
    }
    return false;
}


bool Human::operator<(const Human& other) const {
    if (currentSearchMode == LAST_NAME) {
        return this->lastName < other.lastName;
    } else if (currentSearchMode == FIRST_NAME) {
        return this->firstName < other.firstName;
    } else if (currentSearchMode == MIDDLE_NAME) {
        return this->middleName < other.middleName;
    } else if (currentSearchMode == BIRTH_YEAR) {
        return this->birthday < other.birthday;
    }
    return true; 
}

ostream& operator<<(ostream& os, const Human& human) {
    os << human.lastName << " " << human.firstName << " " << human.middleName << " " << human.birthday;
    return os;
}

istream& operator>>(istream& is, Human& human) {
    bool success = false;
    while (!success) {
        try {
            safeInputString(is, human.lastName, Language::ENGLISH, "Enter last name (English only): ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputString(is, human.firstName, Language::ENGLISH, "Enter first name (English only): ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputString(is, human.middleName, Language::ENGLISH, "Enter middle name (English only): ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputDate(is, human.birthday, "DD/MM/YYYY", "Enter birthday: ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    return is;
}

string Human::getFirstName() const { return this->firstName; }
string Human::getLastName() const { return this->lastName; }
string Human::getMiddleName() const { return this->middleName; }
Date Human::getBirthday() const { return this->birthday; }

void Human::setFirstName(const string& first) { this->firstName = first; }
void Human::setLastName(const string& last) { this->lastName = last; }
void Human::setMiddleName(const string& middle) { this->middleName = middle; }
void Human::setBirthday(const Date& birth) { this->birthday = birth; }
void Human::setSearchMode(SearchMode mode) { currentSearchMode = mode; }
SearchMode Human::currentSearchMode = FULL_MATCH;

void Human:: updateField(int fieldChoice) {
    string str;
    Date date;
    switch(fieldChoice) {
        case 1:
            safeInputString(cin, str, Language::ENGLISH, "New first name (English only): ");
            setFirstName(str);
            break;
        case 2:
            safeInputString(cin, str, Language::ENGLISH, "New last name (English only): ");
            setLastName(str);
            break;
        case 3:
            safeInputString(cin, str, Language::ENGLISH, "New middle name (English only): ");
            setMiddleName(str);
            break;
        case 4:
            safeInputDate(cin, date, "DD/MM/YYYY", "New birthday: ");
            setBirthday(date);
            break;
    }
}