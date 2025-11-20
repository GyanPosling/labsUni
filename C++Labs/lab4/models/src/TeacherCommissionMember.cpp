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

bool TeacherCommissionMember::operator==(const TeacherCommissionMember& other) const {
    return UniversityTeacher::operator==(other) &&
           CommissionMember::operator==(other) &&
           this->commissionWorksCount == other.commissionWorksCount;
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
    cout << "| " << setw(9) << "Last Name" << " | " << setw(10) << "First Name" << " | " << setw(11) << "Middle Name" << " | " << setw(10) << "Birth Year" << " | " << setw(8) << "Position" << " | " << setw(6) << "Degree" << " | " << setw(9) << "Specialty" << " | " << setw(16) << "Scientific Works" << " | " << setw(9) << "Sci Count" << " | " << setw(10) << "Commission" << " | " << setw(12) << "Appoint Year" << " | " << setw(11) << "Certificate" << " | " << setw(13) << "Autobiography" << " | " << setw(9) << "Bio Count" << " | " << setw(10) << "Comm Works" << " | " << setw(10) << "Comm Count" << " |" << endl;}

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
    cout << "| " << setw(9) << getLastName() << " | " << setw(10) << getFirstName() << " | " << setw(11) << getMiddleName() << " | " << setw(10) << getBirthYear() << " | " << setw(8) << UniversityTeacher::getPosition() << " | " << setw(6) << UniversityTeacher::getAcademicDegree() << " | " << setw(9) << UniversityTeacher::getSpecialty() << " | " << setw(16) << scientificWorksStr << " | " << setw(9) << scientificWorksCount << " | " << setw(10) << CommissionMember::getCommissionName() << " | " << setw(12) << CommissionMember::getAppointmentYear() << " | " << setw(11) << CommissionMember::getCertificateNumber() << " | " << setw(13) << autobiographyStr << " | " << setw(9) << autobiographyCount << " | " << setw(10) << commissionWorksStr << " | " << setw(10) << commissionWorksCount << " |" << endl;
}

void TeacherCommissionMember::updatePerson(int fieldChoice){
    string str;
    int num;
    if(fieldChoice <= 9) {
        if(fieldChoice <= 4) {
            Human::updatePerson(fieldChoice);
        } else if(fieldChoice <= 9) {
            UniversityTeacher::updatePerson(fieldChoice);
        }
        return;
    }
    
    switch(fieldChoice) {
        case 10:
            cout << "New commission work: ";
            cin >> str;
            addCommissionWork(str);
            break;
        case 11:
            cout << "Enter number of commission works (0-5): ";
            cin >> num;
            if(num > 5) num = 5;
            for(int i = 0; i < num; i++) {
                cout << "Commission work " << i+1 << ": ";
                cin >> str;
                setCommissionWork(i, str);
            }
            break;
    }
}