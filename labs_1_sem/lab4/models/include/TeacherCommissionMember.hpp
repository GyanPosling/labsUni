#pragma once
#include "Teacher.hpp"
#include "CommissionMember.hpp"

#define COMMISSION_WORKS_SIZE 5

class TeacherCommissionMember : public UniversityTeacher, public CommissionMember {
private:
    string commissionWorks[COMMISSION_WORKS_SIZE];
    int commissionWorksCount;
public:
    TeacherCommissionMember();
    TeacherCommissionMember(const string& first, const string& last, const string& middle, int year,
                           const string& pos, const string& degree, const string& spec,
                           const string& commission, int appYear, const string& cert);
    ~TeacherCommissionMember();
    
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);
    friend ostream& operator<<(ostream& os, const TeacherCommissionMember& tcm);
    friend istream& operator>>(istream& is, TeacherCommissionMember& tcm);
    
    string getFirstName() const { return UniversityTeacher::getFirstName(); }
    string getLastName() const { return UniversityTeacher::getLastName(); }
    string getMiddleName() const { return UniversityTeacher::getMiddleName(); }
    int getBirthYear() const { return UniversityTeacher::getBirthYear(); }
    
    string getCommissionWork(int index) const;
    int getCommissionWorksCount() const;
    int getCommissionWorksSize() const;
    void setCommissionWork(int index, const string& work);
    void addCommissionWork(const string& work);
    
    void printHeader() const override;
    void printTable() const override;
};