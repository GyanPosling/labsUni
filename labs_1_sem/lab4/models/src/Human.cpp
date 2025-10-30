#include "../include/Human.hpp"

Human::Human() : birthYear(0) {}

Human::Human(const string& first, const string& last, const string& middle, int year)
    : firstName(first), lastName(last), middleName(middle), birthYear(year) {}

Human::~Human() {}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        middleName = other.middleName;
        birthYear = other.birthYear;
    }
    return *this;
}

bool Human::operator==(const Human& other) const {
    return firstName == other.firstName &&
           lastName == other.lastName &&
           middleName == other.middleName &&
           birthYear == other.birthYear;
}

bool Human::operator<(const Human& other) const {
    return lastName < other.lastName;
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

string Human::getFirstName() const { return firstName; }
string Human::getLastName() const { return lastName; }
string Human::getMiddleName() const { return middleName; }
int Human::getBirthYear() const { return birthYear; }

void Human::setFirstName(const string& first) { firstName = first; }
void Human::setLastName(const string& last) { lastName = last; }
void Human::setMiddleName(const string& middle) { middleName = middle; }
void Human::setBirthYear(int year) { birthYear = year; }