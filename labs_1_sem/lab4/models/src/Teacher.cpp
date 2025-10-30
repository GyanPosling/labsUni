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
    cout << "| " << setw(10) << "Last Name" << " | " << setw(11) << "First Name" << " | " << setw(12) << "Middle Name" << " | " << setw(11) << "Birth Year" << " | " << setw(9) << "Position" << " | " << setw(7) << "Degree" << " | " << setw(10) << "Specialty" << " | " << setw(17) << "Scientific Works" << " | " << setw(10) << "Sci Count" << " | " << setw(11) << "Commission" << " | " << setw(13) << "Appoint Year" << " | " << setw(12) << "Certificate" << " | " << setw(14) << "Autobiography" << " | " << setw(10) << "Bio Count" << " | " << setw(11) << "Comm Works" << " | " << setw(11) << "Comm Count" << " |" << endl;
}

void UniversityTeacher::printTable() const {
    string scientificWorksStr;
    for (int i = 0; i < this->scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += this->scientificWorks[i];
    }
    cout << left;
    cout << "| " << setw(10) << this->lastName << " | " << setw(11) << this->firstName << " | " << setw(12) << this->middleName << " | " << setw(11) << this->birthYear << " | " << setw(9) << this->position << " | " << setw(7) << this->academicDegree << " | " << setw(10) << this->specialty << " | " << setw(17) << scientificWorksStr << " | " << setw(10) << this->scientificWorksCount << " | " << setw(11) << " - " << " | " << setw(13) << " - " << " | " << setw(12) << " - " << " | " << setw(14) << " - " << " | " << setw(10) << " - " << " | " << setw(11) << " - " << " | " << setw(11) << " - " << " |" << endl;
}