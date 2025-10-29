#include "../include/TeacherCommissionMember.hpp"

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
    is >> static_cast<UniversityTeacher&>(tcm);

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
    cout << left;
    cout << "| " << setw(15) << "Last Name" << " | " << setw(15) << "First Name" << " | " << setw(15) << "Middle Name" << " | " << setw(12) << "Birth Year" << " | " << setw(20) << "Position" << " | " << setw(15) << "Degree" << " | " << setw(20) << "Specialty" << " | " << setw(30) << "Scientific Works" << " | " << setw(10) << "Sci Count" << " | " << setw(20) << "Commission" << " | " << setw(15) << "Appoint Year" << " | " << setw(15) << "Certificate" << " | " << setw(30) << "Autobiography" << " | " << setw(10) << "Bio Count" << " | " << setw(30) << "Comm Works" << " | " << setw(10) << "Comm Count" << " |" << endl;
}

void TeacherCommissionMember::printTable() const {
    string scientificWorksStr;
    for (int i = 0; i < this->scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += this->scientificWorks[i];
    }
    string autobiographyStr;
    for (int i = 0; i < this->autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += this->autobiography[i];
    }
    string commissionWorksStr;
    for (int i = 0; i < this->commissionWorksCount; i++) {
        if (i > 0) commissionWorksStr += ", ";
        commissionWorksStr += this->commissionWorks[i];
    }
    cout << left;
    cout << "| " << setw(15) << this->getLastName() << " | " << setw(15) << this->getFirstName() << " | " << setw(15) << this->getMiddleName() << " | " << setw(12) << this->getBirthYear() << " | " << setw(20) << this->UniversityTeacher::getPosition() << " | " << setw(15) << this->UniversityTeacher::getAcademicDegree() << " | " << setw(20) << this->UniversityTeacher::getSpecialty() << " | " << setw(30) << scientificWorksStr << " | " << setw(10) << this->scientificWorksCount << " | " << setw(20) << this->CommissionMember::getCommissionName() << " | " << setw(15) << this->CommissionMember::getAppointmentYear() << " | " << setw(15) << this->CommissionMember::getCertificateNumber() << " | " << setw(30) << autobiographyStr << " | " << setw(10) << this->autobiographyCount << " | " << setw(30) << commissionWorksStr << " | " << setw(10) << this->commissionWorksCount << " |" << endl;
}