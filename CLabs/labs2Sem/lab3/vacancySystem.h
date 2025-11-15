#ifndef VACANCY_SYSTEM_H
#define VACANCY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_DESCRIPTION_LENGTH 100

typedef struct {
    char description[MAX_DESCRIPTION_LENGTH];
    int len;
} Requirements;

typedef struct {
    char* title;
    int salary;
    Requirements* requirements;
    int experience;
} Vacancy;

typedef struct {
    Vacancy* vacancies;
    int len;
} VacancyStorage;

VacancyStorage* newVacancyStorage(int size);
Vacancy* getVacancyFromUser();
VacancyStorage* addVacancy(VacancyStorage* storage, Vacancy* vacancy);
VacancyStorage* findVacanciesBySalary(VacancyStorage* storage, int salary);
VacancyStorage* deleteVacanciesByTitleLength(VacancyStorage* storage, int minLength);
void printVacancies(VacancyStorage* storage);
void freeVacancy(Vacancy* vacancy);
void freeVacancyStorage(VacancyStorage* storage);

void runStorage();

#endif