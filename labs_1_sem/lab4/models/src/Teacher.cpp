#include "../include/Teacher.hpp"

UniversityTeacher::UniversityTeacher() : Human(), scientificWorksCount(0) {}

UniversityTeacher::UniversityTeacher(const string& first, const string& last, const string& middle, int year,
                                     const string& pos, const string& degree, const string& spec)
    : Human(first, last, middle, year), position(pos), academicDegree(degree), specialty(spec), scientificWorksCount(0) {}

UniversityTeacher::~UniversityTeacher() {}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        position = other.position;
        academicDegree = other.academicDegree;
        specialty = other.specialty;
        scientificWorksCount = other.scientificWorksCount;
        for (int i = 0; i < scientificWorksCount; i++) {
            scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}

bool UniversityTeacher::operator==(const UniversityTeacher& other) const {
    return Human::operator==(other) &&
           position == other.position &&
           academicDegree == other.academicDegree &&
           specialty == other.specialty &&
           scientificWorksCount == other.scientificWorksCount;
}

bool UniversityTeacher::operator<(const UniversityTeacher& other) const {
    return Human::operator<(other);
}

ostream& operator<<(ostream& os, const UniversityTeacher& teacher) {
    os << static_cast<const Human&>(teacher) << " " << teacher.position << " " << teacher.academicDegree << " " << teacher.specialty;
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        os << " " << teacher.scientificWorks[i];
    }
    return os;
}

istream& operator>>(istream& is, UniversityTeacher& teacher) {
    is >> static_cast<Human&>(teacher);
    cout << "Enter position: ";
    is >> teacher.position;
    cout << "Enter academic degree: ";
    is >> teacher.academicDegree;
    cout << "Enter specialty: ";
    is >> teacher.specialty;
    
    cout << "Enter number of scientific works (0-" << SCIENTIFIC_WORKS_SIZE << "): ";
    is >> teacher.scientificWorksCount;
    if (teacher.scientificWorksCount > SCIENTIFIC_WORKS_SIZE) {
        teacher.scientificWorksCount = SCIENTIFIC_WORKS_SIZE;
    }
    
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        cout << "Enter scientific work " << i + 1 << ": ";
        is >> teacher.scientificWorks[i];
    }
    
    return is;
}

string UniversityTeacher::getPosition() const { return position; }
string UniversityTeacher::getAcademicDegree() const { return academicDegree; }
string UniversityTeacher::getSpecialty() const { return specialty; }
string UniversityTeacher::getScientificWork(int index) const { 
    if (index >= 0 && index < scientificWorksCount) return scientificWorks[index];
    return "";
}
int UniversityTeacher::getScientificWorksCount() const { return scientificWorksCount; }
int UniversityTeacher::getScientificWorksSize() const { return SCIENTIFIC_WORKS_SIZE; }

void UniversityTeacher::setPosition(const string& pos) { position = pos; }
void UniversityTeacher::setAcademicDegree(const string& degree) { academicDegree = degree; }
void UniversityTeacher::setSpecialty(const string& spec) { specialty = spec; }
void UniversityTeacher::setScientificWork(int index, const string& work) { 
    if (index >= 0 && index < SCIENTIFIC_WORKS_SIZE) {
        scientificWorks[index] = work;
        if (index >= scientificWorksCount) {
            scientificWorksCount = index + 1;
        }
    }
}
void UniversityTeacher::addScientificWork(const string& work) {
    if (scientificWorksCount < SCIENTIFIC_WORKS_SIZE) {
        scientificWorks[scientificWorksCount] = work;
        scientificWorksCount++;
    }
}

void UniversityTeacher::printHeader() const {
    cout << left;
    cout << "| " << setw(9) << "Last Name" << " | " << setw(10) << "First Name" << " | " << setw(11) << "Middle Name" << " | " << setw(10) << "Birth Year" << " | " << setw(8) << "Position" << " | " << setw(6) << "Degree" << " | " << setw(9) << "Specialty" << " | " << setw(16) << "Scientific Works" << " | " << setw(9) << "Sci Count" << " | " << setw(10) << "Commission" << " | " << setw(12) << "Appoint Year" << " | " << setw(11) << "Certificate" << " | " << setw(13) << "Autobiography" << " | " << setw(9) << "Bio Count" << " | " << setw(10) << "Comm Works" << " | " << setw(10) << "Comm Count" << " |" << endl;}

void UniversityTeacher::printTable() const {
    string scientificWorksStr;
    for (int i = 0; i < this->scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += this->scientificWorks[i];
    }
    cout << left;
    cout << "| " << setw(9) << this->lastName << " | " << setw(10) << this->firstName << " | " << setw(11) << this->middleName << " | " << setw(10) << this->birthYear << " | " << setw(8) << this->position << " | " << setw(6) << this->academicDegree << " | " << setw(9) << this->specialty << " | " << setw(16) << scientificWorksStr << " | " << setw(9) << this->scientificWorksCount << " | " << setw(10) << " - " << " | " << setw(12) << " - " << " | " << setw(11) << " - " << " | " << setw(13) << " - " << " | " << setw(9) << " - " << " | " << setw(10) << " - " << " | " << setw(10) << " - " << " |" << endl;
}