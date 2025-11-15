#include "Teacher.hpp"

UniversityTeacher::UniversityTeacher() : Human(), scientificWorksCount(0) {}

UniversityTeacher::UniversityTeacher(const std::string& first, const std::string& last, const std::string& middle, int year,
                                     const std::string& pos, const std::string& degree, const std::string& spec)
    : Human(first, last, middle, year), position(pos), academicDegree(degree), specialty(spec), scientificWorksCount(0) {}

UniversityTeacher::~UniversityTeacher() {}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        this->position = other.position;
        this->academicDegree = other.academicDegree;
        this->specialty = other.specialty;
        this->scientificWorksCount = other.scientificWorksCount;
        for (int i = 0; i < this->scientificWorksCount; i++) {
            this->scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const UniversityTeacher& teacher) {
    os << static_cast<const Human&>(teacher) << " " << teacher.position << " " << teacher.academicDegree << " " << teacher.specialty;
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        os << " " << teacher.scientificWorks[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, UniversityTeacher& teacher) {
    is >> static_cast<Human&>(teacher);
    std::cout << "Enter position: ";
    is >> teacher.position;
    std::cout << "Enter academic degree: ";
    is >> teacher.academicDegree;
    std::cout << "Enter specialty: ";
    is >> teacher.specialty;
    
    std::cout << "Enter number of scientific works (0-" << SCIENTIFIC_WORKS_SIZE << "): ";
    is >> teacher.scientificWorksCount;
    if (teacher.scientificWorksCount > SCIENTIFIC_WORKS_SIZE) {
        teacher.scientificWorksCount = SCIENTIFIC_WORKS_SIZE;
    }
    
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        std::cout << "Enter scientific work " << i + 1 << ": ";
        is >> teacher.scientificWorks[i];
    }
    
    return is;
}

std::string UniversityTeacher::getPosition() const { return this->position; }
std::string UniversityTeacher::getAcademicDegree() const { return this->academicDegree; }
std::string UniversityTeacher::getSpecialty() const { return this->specialty; }
std::string UniversityTeacher::getScientificWork(int index) const { 
    if (index >= 0 && index < this->scientificWorksCount) return this->scientificWorks[index];
    return "";
}
int UniversityTeacher::getScientificWorksCount() const { return this->scientificWorksCount; }
int UniversityTeacher::getScientificWorksSize() const { return SCIENTIFIC_WORKS_SIZE; }

void UniversityTeacher::setPosition(const std::string& pos) { this->position = pos; }
void UniversityTeacher::setAcademicDegree(const std::string& degree) { this->academicDegree = degree; }
void UniversityTeacher::setSpecialty(const std::string& spec) { this->specialty = spec; }
void UniversityTeacher::setScientificWork(int index, const std::string& work) { 
    if (index >= 0 && index < SCIENTIFIC_WORKS_SIZE) {
        this->scientificWorks[index] = work;
        if (index >= this->scientificWorksCount) {
            this->scientificWorksCount = index + 1;
        }
    }
}
void UniversityTeacher::addScientificWork(const std::string& work) {
    if (this->scientificWorksCount < SCIENTIFIC_WORKS_SIZE) {
        this->scientificWorks[this->scientificWorksCount] = work;
        this->scientificWorksCount++;
    }
}

void UniversityTeacher::printHeader() const {
    cout << " | " << left << setw(15) << "Last Name";
    cout << "| " << left << setw(15) << "First Name";
    cout << "| " << left << setw(15) << "Middle Name";
    cout << "| " << left << setw(12) << "Birth Year";
    cout << "| " << left << setw(20) << "Position";
    cout << "| " << left << setw(15) << "Degree";
    cout << "| " << left << setw(20) << "Specialty";
    cout << "| " << left << setw(15) << "Scientific Works";
    cout << "| " << left << setw(10) << "Works Count" << "|" << endl;
}

void UniversityTeacher::printTable() const {
    cout << " | " << left << setw(15) << this->lastName;
    cout << "| " << left << setw(15) << this->firstName;
    cout << "| " << left << setw(15) << this->middleName;
    cout << "| " << left << setw(12) << this->birthYear;
    cout << "| " << left << setw(20) << this->position;
    cout << "| " << left << setw(15) << this->academicDegree;
    cout << "| " << left << setw(20) << this->specialty;
    
    string scientificWorksStr;
    for (int i = 0; i < this->scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += this->scientificWorks[i];
    }
    cout << "| " << left << setw(15) << scientificWorksStr;
    cout << "| " << left << setw(10) << this->scientificWorksCount << "|" << endl;
}