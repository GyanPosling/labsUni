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
        commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < commissionWorksCount; i++) {
            commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

bool TeacherCommissionMember::operator==(const TeacherCommissionMember& other) const {
    return UniversityTeacher::operator==(other) &&
           CommissionMember::operator==(other) &&
           commissionWorksCount == other.commissionWorksCount;
}

bool TeacherCommissionMember::operator<(const TeacherCommissionMember& other) const {
    return UniversityTeacher::operator<(other);
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
    if (index >= 0 && index < commissionWorksCount) return commissionWorks[index];
    return "";
}

int TeacherCommissionMember::getCommissionWorksCount() const { return commissionWorksCount; }

int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }

void TeacherCommissionMember::setCommissionWork(int index, const string& work) { 
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        commissionWorks[index] = work;
        if (index >= commissionWorksCount) {
            commissionWorksCount = index + 1;
        }
    }
}

void TeacherCommissionMember::addCommissionWork(const string& work) {
    if (commissionWorksCount < COMMISSION_WORKS_SIZE) {
        commissionWorks[commissionWorksCount] = work;
        commissionWorksCount++;
    }
}

void TeacherCommissionMember::printHeader() const {
    cout << left;
    cout << "| " << setw(10) << "Last Name" << " | " << setw(11) << "First Name" << " | " << setw(12) << "Middle Name" << " | " << setw(11) << "Birth Year" << " | " << setw(9) << "Position" << " | " << setw(7) << "Degree" << " | " << setw(10) << "Specialty" << " | " << setw(17) << "Scientific Works" << " | " << setw(10) << "Sci Count" << " | " << setw(11) << "Commission" << " | " << setw(13) << "Appoint Year" << " | " << setw(12) << "Certificate" << " | " << setw(14) << "Autobiography" << " | " << setw(10) << "Bio Count" << " | " << setw(11) << "Comm Works" << " | " << setw(11) << "Comm Count" << " |" << endl;
}

void TeacherCommissionMember::printTable() const {
    string scientificWorksStr;
    for (int i = 0; i < scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += scientificWorks[i];
    }
    string autobiographyStr;
    for (int i = 0; i < autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += autobiography[i];
    }
    string commissionWorksStr;
    for (int i = 0; i < commissionWorksCount; i++) {
        if (i > 0) commissionWorksStr += ", ";
        commissionWorksStr += commissionWorks[i];
    }
    cout << left;
    cout << "| " << setw(10) << getLastName() << " | " << setw(11) << getFirstName() << " | " << setw(12) << getMiddleName() << " | " << setw(11) << getBirthYear() << " | " << setw(9) << UniversityTeacher::getPosition() << " | " << setw(7) << UniversityTeacher::getAcademicDegree() << " | " << setw(10) << UniversityTeacher::getSpecialty() << " | " << setw(17) << scientificWorksStr << " | " << setw(10) << scientificWorksCount << " | " << setw(11) << CommissionMember::getCommissionName() << " | " << setw(13) << CommissionMember::getAppointmentYear() << " | " << setw(12) << CommissionMember::getCertificateNumber() << " | " << setw(14) << autobiographyStr << " | " << setw(10) << autobiographyCount << " | " << setw(11) << commissionWorksStr << " | " << setw(11) << commissionWorksCount << " |" << endl;
}