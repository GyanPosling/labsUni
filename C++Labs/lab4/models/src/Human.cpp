#include "../include/Human.hpp"

Human::Human() : birthYear(0) {}

Human::Human(const string& first, const string& last, const string& middle, int year)
    : firstName(first), lastName(last), middleName(middle), birthYear(year) {}

Human::~Human() {}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->middleName = other.middleName;
        this->birthYear = other.birthYear;
    }
    return *this;
}

bool Human::operator==(const Human& other) const {
    if (currentSearchMode == FULL_MATCH) {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               middleName == other.middleName &&
               birthYear == other.birthYear;
    } else if (currentSearchMode == LAST_NAME) {
        return lastName == other.lastName;
    } else if (currentSearchMode == FIRST_NAME) {
        return firstName == other.firstName;
    } else if (currentSearchMode == MIDDLE_NAME) {
        return middleName == other.middleName;
    } else if (currentSearchMode == BIRTH_YEAR) {
        return birthYear == other.birthYear;
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
        return this->birthYear < other.birthYear;
    }
    return true; 
}

ostream& operator<<(ostream& os, const Human& human) {
    os << human.lastName << " " << human.firstName << " " << human.middleName << " " << human.birthYear;
    return os;
}

istream& operator>>(istream& is, Human& human) {
    cout << "Enter last name: ";
    is >> human.lastName;
    cout << "Enter first name: "; 
    is >> human.firstName;
    cout << "Enter middle name: ";
    is >> human.middleName;
    cout << "Enter birth year: ";
    is >> human.birthYear;
    return is;
}

string Human::getFirstName() const { return this->firstName; }
string Human::getLastName() const { return this->lastName; }
string Human::getMiddleName() const { return this->middleName; }
int Human::getBirthYear() const { return this->birthYear; }

void Human::setFirstName(const string& first) { this->firstName = first; }
void Human::setLastName(const string& last) { this->lastName = last; }
void Human::setMiddleName(const string& middle) { this->middleName = middle; }
void Human::setBirthYear(int year) { this->birthYear = year; }
void Human::setSearchMode(SearchMode mode) { currentSearchMode = mode; }
SearchMode Human::currentSearchMode = FULL_MATCH;