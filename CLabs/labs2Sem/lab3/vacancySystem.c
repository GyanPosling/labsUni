#include "vacancySystem.h"
#include "validators.h"

VacancyStorage* newVacancyStorage(int size) {
    VacancyStorage* storage = (VacancyStorage*)malloc(sizeof(VacancyStorage));
    storage->vacancies = (Vacancy*)malloc(sizeof(Vacancy) * size);
    storage->len = 0;
    return storage;
}

Vacancy* getVacancyFromUser() {
    Vacancy* vacancy = (Vacancy*)malloc(sizeof(Vacancy));
    printf("Enter title: ");
    vacancy->title = initString();
    printf("Enter salary: ");
    vacancy->salary = getValidInput(0, 1000000);
    vacancy->requirements = (Requirements*)malloc(sizeof(Requirements));
    printf("Enter requirements: ");
    fgets(vacancy->requirements->description, MAX_DESCRIPTION_LENGTH, stdin);
    size_t len = strlen(vacancy->requirements->description);
    if (len > 0 && vacancy->requirements->description[len - 1] == '\n') {
        vacancy->requirements->description[len - 1] = '\0';
    }
    printf("Enter required experience (in years): ");
    vacancy->experience = getValidInput(0, 50);
    return vacancy;
}

VacancyStorage* addVacancy(VacancyStorage* storage, Vacancy* vacancy) {
    storage->vacancies = (Vacancy*)realloc(storage->vacancies, sizeof(Vacancy) * (storage->len + 1));
    storage->vacancies[storage->len] = *vacancy;
    storage->len++;
    return storage;
}

VacancyStorage* findVacanciesBySalary(VacancyStorage* storage, int salary) {
    VacancyStorage* result = newVacancyStorage(0);
    for (int i = 0; i < storage->len; i++) {
        if (storage->vacancies[i].salary == salary) {
            result->vacancies = (Vacancy*)realloc(result->vacancies, sizeof(Vacancy) * (result->len + 1));
            result->vacancies[result->len] = storage->vacancies[i];
            result->len++;
        }
    }
    return result;
}

VacancyStorage* deleteVacanciesByTitleLength(VacancyStorage* storage, int minLength) {
    int newLen = 0;
    for (int i = 0; i < storage->len; i++) {
        if (strlen(storage->vacancies[i].title) >= minLength) {
            storage->vacancies[newLen++] = storage->vacancies[i];
        } else {
            freeVacancy(&storage->vacancies[i]);
        }
    }
    storage->len = newLen;
    if (newLen == 0) {
        free(storage->vacancies);
        storage->vacancies = NULL;
    } else {
        Vacancy* temp = realloc(storage->vacancies, sizeof(Vacancy) * newLen);
        if (!temp) {
            printf("Memory reallocation failed. Not enough memory.\n");
            return storage;
        }
        storage->vacancies = temp;
    }
    return storage;
}

void printVacancies(VacancyStorage* storage) {
    for (int i = 0; i < storage->len; i++) {
        printf("Title: %s\n", storage->vacancies[i].title);
        printf("Salary: %d\n", storage->vacancies[i].salary);
        printf("Requirements: %s\n", storage->vacancies[i].requirements->description);
        printf("Experience: %d years\n\n", storage->vacancies[i].experience);
    }
}

void freeVacancy(Vacancy* vacancy) {
    if (vacancy->title) free(vacancy->title);
    if (vacancy->requirements) {
        free(vacancy->requirements);
    }
}

void freeVacancyStorage(VacancyStorage* storage) {
    if (!storage) return;
    for (int i = 0; i < storage->len; i++) {
        freeVacancy(&storage->vacancies[i]);
    }
    free(storage->vacancies);
    free(storage);
}

void runStorage() {
    VacancyStorage* storage = newVacancyStorage(1);
    int choice;
    do {
        printf("\nMenu\n");
        printf("1. Add a vacancy\n");
        printf("2. Delete vacancies by title length\n");
        printf("3. Show all vacancies\n");
        printf("4. Find vacancies by salary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = getValidInput(1, 5);
        switch (choice) {
            case 1: {
                Vacancy* newVacancy = getVacancyFromUser();
                storage = addVacancy(storage, newVacancy);
                free(newVacancy);
                break;
            }
            case 2: {
                printf("Enter minimum title length: ");
                int minLength = getValidInput(0, 100);
                storage = deleteVacanciesByTitleLength(storage, minLength);
                printf("If a vacancy was found, it was deleted.\n");
                printVacancies(storage);
                break;
            }
            case 3:
                printf("\nAll vacancies:\n");
                printVacancies(storage);
                break;
            case 4: {
                printf("Enter salary to search: ");
                int salary = getValidInput(0, 1000000);
                VacancyStorage* found = findVacanciesBySalary(storage, salary);
                printf("\nFound vacancies:\n");
                printVacancies(found);
                freeVacancyStorage(found);
                break;
            }
            case 5:
                printf("Exited\n");
                break;
        }
    } while (choice != 5);
    freeVacancyStorage(storage);
}