#pragma once
#include "Human.hpp"
#include<string>
using namespace std;

#define SCIENTIFIC_WORKS_SIZE 5

class UniversityTeacher : virtual public Human {
protected:
    string position;
    string academicDegree;
    string specialty;
    string scientificWorks[SCIENTIFIC_WORKS_SIZE];
    int scientificWorksCount;
public:
    UniversityTeacher();
    UniversityTeacher(const string& first, const string& last, const string& middle, int year,
                     const string& pos, const string& degree, const string& spec);
    ~UniversityTeacher();
    
    UniversityTeacher& operator=(const UniversityTeacher& other);
    friend ostream& operator<<(ostream& os, const UniversityTeacher& teacher);
    friend istream& operator>>(istream& is, UniversityTeacher& teacher);
    
    string getPosition() const;
    string getAcademicDegree() const;
    string getSpecialty() const;
    string getScientificWork(int index) const;
    int getScientificWorksCount() const;
    int getScientificWorksSize() const;
    
    void setPosition(const string& pos);
    void setAcademicDegree(const string& degree);
    void setSpecialty(const string& spec);
    void setScientificWork(int index, const string& work);
    void addScientificWork(const string& work);
    
    void printHeader() const override;
    void printTable() const override;
};