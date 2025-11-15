#pragma once
#include "Human.hpp"
#include<string>
using namespace std;

#define AUTOBIOGRAPHY_SIZE 10

class CommissionMember :virtual public Human {
protected:
    string commissionName;
    int appointmentYear;
    string certificateNumber;
    string autobiography[AUTOBIOGRAPHY_SIZE];
    int autobiographyCount;
public:
    CommissionMember();
    CommissionMember(const string& first, const string& last, const string& middle, int year,
                    const string& commission, int appYear, const string& cert);
    ~CommissionMember();
    
    CommissionMember& operator=(const CommissionMember& other);
    friend ostream& operator<<(ostream& os, const CommissionMember& member);
    friend istream& operator>>(istream& is, CommissionMember& member);
    
    string getCommissionName() const;
    int getAppointmentYear() const;
    string getCertificateNumber() const;
    string getAutobiography(int index) const;
    int getAutobiographyCount() const;
    int getAutobiographySize() const;
    
    void setCommissionName(const string& name);
    void setAppointmentYear(int year);
    void setCertificateNumber(const string& number);
    void setAutobiography(int index, const string& bio);
    void addAutobiography(const string& bio);
    
    void printHeader() const override;
    void printTable() const override;
};