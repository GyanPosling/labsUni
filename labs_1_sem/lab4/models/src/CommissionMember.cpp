#include "../include/CommissionMember.hpp"

CommissionMember::CommissionMember() : Human(), appointmentYear(0), autobiographyCount(0) {}

CommissionMember::CommissionMember(const string& first, const string& last, const string& middle, int year,
                                   const string& commission, int appYear, const string& cert)
    : Human(first, last, middle, year), commissionName(commission), appointmentYear(appYear), certificateNumber(cert), autobiographyCount(0) {}

CommissionMember::~CommissionMember() {}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        commissionName = other.commissionName;
        appointmentYear = other.appointmentYear;
        certificateNumber = other.certificateNumber;
        autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < autobiographyCount; i++) {
            autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}

bool CommissionMember::operator==(const CommissionMember& other) const {
    return Human::operator==(other) &&
           commissionName == other.commissionName &&
           appointmentYear == other.appointmentYear &&
           certificateNumber == other.certificateNumber &&
           autobiographyCount == other.autobiographyCount;
}

bool CommissionMember::operator<(const CommissionMember& other) const {
    return Human::operator<(other);
}

ostream& operator<<(ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName << " " << member.appointmentYear << " " << member.certificateNumber;
    for (int i = 0; i < member.autobiographyCount; i++) {
        os << " " << member.autobiography[i];
    }
    return os;
}

istream& operator>>(istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member);
    cout << "Enter commission name: ";
    is >> member.commissionName;
    cout << "Enter appointment year: ";
    is >> member.appointmentYear;
    cout << "Enter certificate number: ";
    is >> member.certificateNumber;
    
    cout << "Enter number of autobiography entries (0-" << AUTOBIOGRAPHY_SIZE << "): ";
    is >> member.autobiographyCount;
    if (member.autobiographyCount > AUTOBIOGRAPHY_SIZE) {
        member.autobiographyCount = AUTOBIOGRAPHY_SIZE;
    }
    
    for (int i = 0; i < member.autobiographyCount; i++) {
        cout << "Enter autobiography entry " << i + 1 << ": ";
        is >> member.autobiography[i];
    }
    
    return is;
}

string CommissionMember::getCommissionName() const { return commissionName; }
int CommissionMember::getAppointmentYear() const { return appointmentYear; }
string CommissionMember::getCertificateNumber() const { return certificateNumber; }
string CommissionMember::getAutobiography(int index) const { 
    if (index >= 0 && index < autobiographyCount) return autobiography[index];
    return "";
}
int CommissionMember::getAutobiographyCount() const { return autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }

void CommissionMember::setCommissionName(const string& name) { commissionName = name; }
void CommissionMember::setAppointmentYear(int year) { appointmentYear = year; }
void CommissionMember::setCertificateNumber(const string& number) { certificateNumber = number; }
void CommissionMember::setAutobiography(int index, const string& bio) { 
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        autobiography[index] = bio;
        if (index >= autobiographyCount) {
            autobiographyCount = index + 1;
        }
    }
}
void CommissionMember::addAutobiography(const string& bio) {
    if (autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        autobiography[autobiographyCount] = bio;
        autobiographyCount++;
    }
}

void CommissionMember::printHeader() const {
    cout << left;
    cout << "| " << setw(10) << "Last Name" << " | " << setw(11) << "First Name" << " | " << setw(12) << "Middle Name" << " | " << setw(11) << "Birth Year" << " | " << setw(9) << "Position" << " | " << setw(7) << "Degree" << " | " << setw(10) << "Specialty" << " | " << setw(17) << "Scientific Works" << " | " << setw(10) << "Sci Count" << " | " << setw(11) << "Commission" << " | " << setw(13) << "Appoint Year" << " | " << setw(12) << "Certificate" << " | " << setw(14) << "Autobiography" << " | " << setw(10) << "Bio Count" << " | " << setw(11) << "Comm Works" << " | " << setw(11) << "Comm Count" << " |" << endl;
}

void CommissionMember::printTable() const {
    string autobiographyStr;
    for (int i = 0; i < this->autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += this->autobiography[i];
    }
    cout << left;
    cout << "| " << setw(10) << this->lastName << " | " << setw(11) << this->firstName << " | " << setw(12) << this->middleName << " | " << setw(11) << this->birthYear << " | " << setw(9) << " - " << " | " << setw(7) << " - " << " | " << setw(10) << " - " << " | " << setw(17) << " - " << " | " << setw(10) << " - " << " | " << setw(11) << this->commissionName << " | " << setw(13) << this->appointmentYear << " | " << setw(12) << this->certificateNumber << " | " << setw(14) << autobiographyStr << " | " << setw(10) << this->autobiographyCount << " | " << setw(11) << " - " << " | " << setw(11) << " - " << " |" << endl;
}