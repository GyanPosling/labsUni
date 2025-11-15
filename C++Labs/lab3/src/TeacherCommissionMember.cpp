#include "TeacherCommissionMember.hpp"

TeacherCommissionMember::TeacherCommissionMember() : Human(), UniversityTeacher(), CommissionMember(), commissionWorksCount(0) {}

TeacherCommissionMember::TeacherCommissionMember(const string& first, const string& last, const string& middle, int year,
                                                 const string& pos, const string& degree, const string& spec,
                                                 const string& commission, int appYear, const string& cert)
    : Human(first, last, middle, year),
      UniversityTeacher(first, last, middle, year, pos, degree, spec),
      CommissionMember(first, last, middle, year, commission, appYear, cert),
      commissionWorksCount(0) {}

TeacherCommissionMember::~TeacherCommissionMember() {}

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        this->commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < this->commissionWorksCount; i++) {
            this->commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const TeacherCommissionMember& tcm) {
    os << static_cast<const Human&>(tcm) << " " << tcm.UniversityTeacher::getPosition() << " " 
       << tcm.UniversityTeacher::getAcademicDegree() << " " << tcm.UniversityTeacher::getSpecialty()
       << " " << tcm.CommissionMember::getCommissionName() << " " << tcm.CommissionMember::getAppointmentYear()
       << " " << tcm.CommissionMember::getCertificateNumber();
    
    for (int i = 0; i < tcm.UniversityTeacher::getScientificWorksCount(); i++) {
        os << " " << tcm.UniversityTeacher::getScientificWork(i);
    }
    
    for (int i = 0; i < tcm.CommissionMember::getAutobiographyCount(); i++) {
        os << " " << tcm.CommissionMember::getAutobiography(i);
    }
    
    for (int i = 0; i < tcm.commissionWorksCount; i++) {
        os << " " << tcm.commissionWorks[i];
    }
    
    return os;
}

istream& operator>>(istream& is, TeacherCommissionMember& tcm) {
    cout << "=== Enter Human Data ===" << endl;
    cout << "Enter last name: ";
    is >> tcm.lastName;
    cout << "Enter first name: ";
    is >> tcm.firstName;
    cout << "Enter middle name: ";
    is >> tcm.middleName;
    cout << "Enter birth year: ";
    is >> tcm.birthYear;

    cout << "=== Enter UniversityTeacher Data ===" << endl;
    cout << "Enter position: ";
    is >> tcm.position;
    cout << "Enter academic degree: ";
    is >> tcm.academicDegree;
    cout << "Enter specialty: ";
    is >> tcm.specialty;

    cout << "Enter number of scientific works (0-" << SCIENTIFIC_WORKS_SIZE << "): ";
    is >> tcm.scientificWorksCount;
    if (tcm.scientificWorksCount > SCIENTIFIC_WORKS_SIZE) {
        tcm.scientificWorksCount = SCIENTIFIC_WORKS_SIZE;
    }
    for (int i = 0; i < tcm.scientificWorksCount; i++) {
        cout << "Enter scientific work " << i + 1 << ": ";
        is >> tcm.scientificWorks[i];
    }

    cout << "=== Enter CommissionMember Data ===" << endl;
    cout << "Enter commission name: ";
    is >> tcm.commissionName;
    cout << "Enter appointment year: ";
    is >> tcm.appointmentYear;
    cout << "Enter certificate number: ";
    is >> tcm.certificateNumber;

    cout << "Enter number of autobiography entries (0-" << AUTOBIOGRAPHY_SIZE << "): ";
    is >> tcm.autobiographyCount;
    if (tcm.autobiographyCount > AUTOBIOGRAPHY_SIZE) {
        tcm.autobiographyCount = AUTOBIOGRAPHY_SIZE;
    }
    for (int i = 0; i < tcm.autobiographyCount; i++) {
        cout << "Enter autobiography entry " << i + 1 << ": ";
        is >> tcm.autobiography[i];
    }

    cout << "=== Enter TeacherCommissionMember Data ===" << endl;
    cout << "Enter number of commission works (0-" << COMMISSION_WORKS_SIZE << "): ";
    is >> tcm.commissionWorksCount;
    if (tcm.commissionWorksCount > COMMISSION_WORKS_SIZE) {
        tcm.commissionWorksCount = COMMISSION_WORKS_SIZE;
    }
    for (int i = 0; i < tcm.commissionWorksCount; i++) {
        cout << "Enter commission work " << i + 1 << ": ";
        is >> tcm.commissionWorks[i];
    }

    return is;
}

string TeacherCommissionMember::getCommissionWork(int index) const { 
    if (index >= 0 && index < this->commissionWorksCount) return this->commissionWorks[index];
    return "";
}

int TeacherCommissionMember::getCommissionWorksCount() const { return this->commissionWorksCount; }

int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }

void TeacherCommissionMember::setCommissionWork(int index, const string& work) { 
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        this->commissionWorks[index] = work;
        if (index >= this->commissionWorksCount) {
            this->commissionWorksCount = index + 1;
        }
    }
}

void TeacherCommissionMember::addCommissionWork(const string& work) {
    if (this->commissionWorksCount < COMMISSION_WORKS_SIZE) {
        this->commissionWorks[this->commissionWorksCount] = work;
        this->commissionWorksCount++;
    }
}

void TeacherCommissionMember::printHeader() const {
    cout << " | " << left << setw(15) << "Last Name";
    cout << "| " << left << setw(15) << "First Name";
    cout << "| " << left << setw(15) << "Middle Name";
    cout << "| " << left << setw(12) << "Birth Year";
    cout << "| " << left << setw(20) << "Position";
    cout << "| " << left << setw(15) << "Degree";
    cout << "| " << left << setw(20) << "Specialty";
    cout << "| " << left << setw(20) << "Commission";
    cout << "| " << left << setw(15) << "Appoint Year";
    cout << "| " << left << setw(15) << "Certificate";
    cout << "| " << left << setw(20) << "Commission Works";
    cout << "| " << left << setw(10) << "Works Count" << "|" << endl;
}

void TeacherCommissionMember::printTable() const {
    cout << " | " << left << setw(15) << this->getLastName();
    cout << "| " << left << setw(15) << this->getFirstName();
    cout << "| " << left << setw(15) << this->getMiddleName();
    cout << "| " << left << setw(12) << this->getBirthYear();
    cout << "| " << left << setw(20) << this->UniversityTeacher::getPosition();
    cout << "| " << left << setw(15) << this->UniversityTeacher::getAcademicDegree();
    cout << "| " << left << setw(20) << this->UniversityTeacher::getSpecialty();
    cout << "| " << left << setw(20) << this->CommissionMember::getCommissionName();
    cout << "| " << left << setw(15) << this->CommissionMember::getAppointmentYear();
    cout << "| " << left << setw(15) << this->CommissionMember::getCertificateNumber();
    
    string commissionWorksStr;
    for (int i = 0; i < this->commissionWorksCount; i++) {
        if (i > 0) commissionWorksStr += ", ";
        commissionWorksStr += this->commissionWorks[i];
    }
    cout << "| " << left << setw(20) << commissionWorksStr;
    cout << "| " << left << setw(10) << this->commissionWorksCount << "|" << endl;
}