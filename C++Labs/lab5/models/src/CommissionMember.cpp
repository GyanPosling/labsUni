#include "../include/CommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"

CommissionMember::CommissionMember() : Human(), appointmentDate(), autobiographyCount(0) {}

CommissionMember::CommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                   const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth), commissionName(commission), appointmentDate(appDate), certificateNumber(cert), autobiographyCount(0) {}

CommissionMember::~CommissionMember() {}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        this->commissionName = other.commissionName;
        this->appointmentDate = other.appointmentDate;
        this->certificateNumber = other.certificateNumber;
        this->autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < autobiographyCount; i++) {
            this->autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}

bool CommissionMember::operator==(const CommissionMember& other) const {
    return Human::operator==(other) &&
           this->commissionName == other.commissionName &&
           this->appointmentDate == other.appointmentDate &&
           this->certificateNumber == other.certificateNumber &&
           this->autobiographyCount == other.autobiographyCount;
}

bool CommissionMember::operator<(const CommissionMember& other) const {
    return Human::operator<(other);
}

ostream& operator<<(ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName << " " << member.appointmentDate << " " << member.certificateNumber;
    for (int i = 0; i < member.autobiographyCount; i++) {
        os << " " << member.autobiography[i];
    }
    return os;
}

istream& operator>>(istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member);
    
    bool success = false;
    while (!success) {
        try {
            safeInputText(is, member.commissionName, "Enter commission name: ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputDate(is, member.appointmentDate, "DD/MM/YYYY", "Enter appointment date: ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputText(is, member.certificateNumber, "Enter certificate number: ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    success = false;
    while (!success) {
        try {
            safeInputInt(is, member.autobiographyCount, 0, AUTOBIOGRAPHY_SIZE, "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    for (int i = 0; i < member.autobiographyCount; i++) {
        success = false;
        while (!success) {
            try {
                safeInputText(is, member.autobiography[i], "Enter autobiography entry " + to_string(i + 1) + ": ");
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
    
    return is;
}

string CommissionMember::getCommissionName() const { return this->commissionName; }
Date CommissionMember::getAppointmentDate() const { return this->appointmentDate; }
string CommissionMember::getCertificateNumber() const { return this->certificateNumber; }
string CommissionMember::getAutobiography(int index) const { 
    if (index >= 0 && index < autobiographyCount) return this->autobiography[index];
    return "";
}
int CommissionMember::getAutobiographyCount() const { return this->autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }

void CommissionMember::setCommissionName(const string& name) { this->commissionName = name; }
void CommissionMember::setAppointmentDate(const Date& date) { this->appointmentDate = date; }
void CommissionMember::setCertificateNumber(const string& number) { this->certificateNumber = number; }
void CommissionMember::setAutobiography(int index, const string& bio) { 
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        this->autobiography[index] = bio;
        if (index >= this->autobiographyCount) {
            this->autobiographyCount = index + 1;
        }
    }
}
void CommissionMember::addAutobiography(const string& bio) {
    if (this->autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        this->autobiography[autobiographyCount] = bio;
        this->autobiographyCount++;
    }
}

void CommissionMember::printHeader() const {
    cout << left;
    cout << "| " << setw(9) << "Last Name" << " | " << setw(10) << "First Name" << " | " << setw(11) << "Middle Name" << " | " << setw(10) << "Birth Year" << " | " << setw(8) << "Position" << " | " << setw(6) << "Degree" << " | " << setw(9) << "Specialty" << " | " << setw(16) << "Scientific Works" << " | " << setw(9) << "Sci Count" << " | " << setw(10) << "Commission" << " | " << setw(12) << "Appoint Year" << " | " << setw(11) << "Certificate" << " | " << setw(13) << "Autobiography" << " | " << setw(9) << "Bio Count" << " | " << setw(10) << "Comm Works" << " | " << setw(10) << "Comm Count" << " |" << endl;
}

void CommissionMember::printTable() const {
    string autobiographyStr;
    for (int i = 0; i < this->autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += this->autobiography[i];
    }
    cout << left;
    cout << "| " << setw(9) << this->lastName << " | " << setw(10) << this->firstName << " | " << setw(11) << this->middleName << " | " << setw(10) << this->birthday << " | " << setw(8) << " - " << " | " << setw(6) << " - " << " | " << setw(9) << " - " << " | " << setw(16) << " - " << " | " << setw(9) << " - " << " | " << setw(10) << this->commissionName << " | " << setw(12) << this->appointmentDate << " | " << setw(11) << this->certificateNumber << " | " << setw(13) << autobiographyStr << " | " << setw(9) << this->autobiographyCount << " | " << setw(10) << " - " << " | " << setw(10) << " - " << " |" << endl;
}