#include "Human.hpp"

Human::Human() : birthYear(0) {}

Human::Human(const std::string& first, const std::string& last, const std::string& middle, int year)
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

std::ostream& operator<<(std::ostream& os, const Human& human) {
    os << human.lastName << " " << human.firstName << " " << human.middleName << " " << human.birthYear;
    return os;
}

std::istream& operator>>(std::istream& is, Human& human) {
    std::cout << "Enter last name: ";
    is >> human.lastName;
    std::cout << "Enter first name: ";
    is >> human.firstName;
    std::cout << "Enter middle name: ";
    is >> human.middleName;
    std::cout << "Enter birth year: ";
    is >> human.birthYear;
    return is;
}

std::string Human::getFirstName() const { return this->firstName; }
std::string Human::getLastName() const { return this->lastName; }
std::string Human::getMiddleName() const { return this->middleName; }
int Human::getBirthYear() const { return this->birthYear; }

void Human::setFirstName(const std::string& first) { this->firstName = first; }
void Human::setLastName(const std::string& last) { this->lastName = last; }
void Human::setMiddleName(const std::string& middle) { this->middleName = middle; }
void Human::setBirthYear(int year) { this->birthYear = year; }