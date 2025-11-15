#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "../models/include/Human.hpp"
#include "../models/include/Teacher.hpp"
#include "../models/include/CommissionMember.hpp"
#include "../models/include/TeacherCommissionMember.hpp"
#include "../templates/include/Deque.hpp"
#include "../exceptions/include/InputHandler.hpp"
#include "../exceptions/include/Date.hpp"
using namespace std;


void drawMenu(const string& title, const string options[], int numOptions) {
    int max_len = title.length();
    for (int i = 0; i < numOptions; i++) {
        if (options[i].length() > max_len) max_len = options[i].length();
    }
    max_len += 4;
    cout << "+" << string(max_len, '-') << "+" << endl;
    cout << "| " << title << string(max_len - title.length() - 1, ' ') << "|" << endl;
    cout << "+" << string(max_len, '-') << "+" << endl;
    for (int i = 0; i < numOptions; i++) {
        cout << "| " << options[i] << string(max_len - options[i].length() - 1, ' ') << "|" << endl;
    }
    cout << "+" << string(max_len, '-') << "+" << endl;
}

int getChoice(int max) {
    int choice;
    bool success = false;
    while (!success) {
        try {
            safeInputInt(cin, choice, 1, max, "Enter choice (1-" + to_string(max) + "): ");
            success = true;
        } catch (const InputException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return choice;
}

void addObject(Deque<Human*>& deque) {
    string sideOptions[2] = {"1. Add to Front", "2. Add to Back"};
    drawMenu("Select Side", sideOptions, 2);
    int sideChoice = getChoice(2);
    
    string typeOptions[3] = {"1. Teacher", "2. Commission Member", "3. Teacher Commission Member"};
    drawMenu("Select Type", typeOptions, 3);
    int typeChoice = getChoice(3);
    
    Human* object;
    if (typeChoice == 1) {
        UniversityTeacher* teacher = new UniversityTeacher();
        cin >> *teacher;
        object = teacher;
    } else if (typeChoice == 2) {
        CommissionMember* commissionMember = new CommissionMember();
        cin >> *commissionMember;
        object = commissionMember;
    } else {
        TeacherCommissionMember* teacherCommissionMember = new TeacherCommissionMember();
        cin >> *teacherCommissionMember;
        object = teacherCommissionMember;
    }
    
    if (sideChoice == 1) {
        deque.pushFront(object);
    } else {
        deque.pushBack(object);
    }
}

void removeObject(Deque<Human*>& deque) {
    string options[2] = {"1. Remove from Front", "2. Remove from Back"};
    drawMenu("Remove Object", options, 2);
    int choice = getChoice(2);
    
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    if (choice == 1) {
        delete deque.peekFirst();
        deque.popFront();
        cout << "Removed from front." << endl;
    } else {
        delete deque.peekLast();
        deque.popBack();
        cout << "Removed from back." << endl;
    }
}

void updateHumanFields(Human* human) {
    string str;
    Date date;
    string options[4] = {"1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday"};
    drawMenu("Select Human Field", options, 4);
    int choice = getChoice(4);
    if (choice == 1) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, str, Language::ENGLISH, "New first name (English only): ");
                human->setFirstName(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 2) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, str, Language::ENGLISH, "New last name (English only): ");
                human->setLastName(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 3) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, str, Language::ENGLISH, "New middle name (English only): ");
                human->setMiddleName(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else {
        bool success = false;
        while (!success) {
            try {
                safeInputDate(cin, date, "DD/MM/YYYY", "New birthday: ");
                human->setBirthday(date);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
}

void updateTeacherFields(UniversityTeacher* teacher) {
    string str;
    int num;
    string options[5] = {"1. Position", "2. Degree", "3. Specialty", "4. Add Scientific Work", "5. Replace All Scientific Works"};
    drawMenu("Select Teacher Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New position: ");
                teacher->setPosition(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 2) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New degree: ");
                teacher->setAcademicDegree(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 3) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New specialty: ");
                teacher->setSpecialty(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 4) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New scientific work: ");
                teacher->addScientificWork(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else {
        bool success = false;
        while (!success) {
            try {
                safeInputInt(cin, num, 0, 5, "Enter number of scientific works (0-5): ");
                for (int i = 0; i < num; i++) {
                    bool innerSuccess = false;
                    while (!innerSuccess) {
                        try {
                            safeInputText(cin, str, "Scientific work " + to_string(i+1) + ": ");
                            teacher->setScientificWork(i, str);
                            innerSuccess = true;
                        } catch (const InputException& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
}

void updateCommissionFields(CommissionMember* commissionMember) {
    string str;
    int num;
    Date date;
    string options[5] = {"1. Commission Name", "2. Appointment Date", "3. Certificate Number", "4. Add Autobiography", "5. Replace All Autobiography"};
    drawMenu("Select Commission Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New commission name: ");
                commissionMember->setCommissionName(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 2) {
        bool success = false;
        while (!success) {
            try {
                safeInputDate(cin, date, "DD/MM/YYYY", "New appointment date: ");
                commissionMember->setAppointmentDate(date);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 3) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New certificate number: ");
                commissionMember->setCertificateNumber(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 4) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New autobiography: ");
                commissionMember->addAutobiography(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else {
        bool success = false;
        while (!success) {
            try {
                safeInputInt(cin, num, 0, 10, "Enter number of autobiography (0-10): ");
                for (int i = 0; i < num; i++) {
                    bool innerSuccess = false;
                    while (!innerSuccess) {
                        try {
                            safeInputText(cin, str, "Autobiography " + to_string(i+1) + ": ");
                            commissionMember->setAutobiography(i, str);
                            innerSuccess = true;
                        } catch (const InputException& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
}

void updateTeacherCommissionMemberFields(TeacherCommissionMember* teacherCommissionMember) {
    string str;
    int num;
    string options[2] = {"1. Add Commission Work", "2. Replace All Commission Works"};
    drawMenu("Select TCM Extra Field", options, 2);
    int choice = getChoice(2);
    if (choice == 1) {
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, str, "New commission work: ");
                teacherCommissionMember->addCommissionWork(str);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else {
        bool success = false;
        while (!success) {
            try {
                safeInputInt(cin, num, 0, 5, "Enter number of commission works (0-5): ");
                for (int i = 0; i < num; i++) {
                    bool innerSuccess = false;
                    while (!innerSuccess) {
                        try {
                            safeInputText(cin, str, "Commission work " + to_string(i+1) + ": ");
                            teacherCommissionMember->setCommissionWork(i, str);
                            innerSuccess = true;
                        } catch (const InputException& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
}

void modifyObject(Deque<Human*>& deque) {
    string sideOptions[2] = {"1. Modify First", "2. Modify Last"};
    drawMenu("Select Object to Modify", sideOptions, 2);
    int sideChoice = getChoice(2);
    
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    Human* human = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();
    
    TeacherCommissionMember* teacherCommissionMember = dynamic_cast<TeacherCommissionMember*>(human);
    UniversityTeacher* teacher = dynamic_cast<UniversityTeacher*>(human);
    CommissionMember* commissionMember = dynamic_cast<CommissionMember*>(human);
    
    string modifyOptions[2] = {"1. Change All Data", "2. Change Specific Field"};
    drawMenu("Modify Options", modifyOptions, 2);
    int modifyChoice = getChoice(2);
    
    if (modifyChoice == 1) {
        if (teacherCommissionMember) {
            cin >> *teacherCommissionMember;
        } else if (teacher) {
            cin >> *teacher;
        } else if (commissionMember) {
            cin >> *commissionMember;
        } else {
            cin >> *human;
        }
        return;
    }
    
    int numFieldOptions = 1;
    string fieldOptions[7];
    fieldOptions[0] = "1. Human Fields";
    
    if (teacher) {
        fieldOptions[numFieldOptions++] = "2. Teacher Fields";
    }
    if (commissionMember) {
        fieldOptions[numFieldOptions++] = "3. Commission Fields";
    }
    if (teacherCommissionMember) {
        fieldOptions[numFieldOptions++] = "4. TCM Extra Fields";
    }
    
    drawMenu("Select Field Category", fieldOptions, numFieldOptions);
    int fieldChoice = getChoice(numFieldOptions);
    
    if (fieldChoice == 1) {
        updateHumanFields(human);
    } else if (fieldChoice == 2 && teacher) {
        updateTeacherFields(teacher);
    } else if (fieldChoice == 3 && commissionMember) {
        updateCommissionFields(commissionMember);
    } else if (fieldChoice == 4 && teacherCommissionMember) {
        updateTeacherCommissionMemberFields(teacherCommissionMember);
    }
}

void peekObject(Deque<Human*>& deque) {
    string options[2] = {"1. Peek First", "2. Peek Last"};
    drawMenu("Peek Object", options, 2);
    int choice = getChoice(2);
    
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    Human* human = (choice == 1) ? deque.peekFirst() : deque.peekLast();
    
    if (!deque.isEmpty()) {
        TeacherCommissionMember tcm;
        tcm.printHeader();
        human->printTable();
    }
}

void printDeque(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    if (!deque.isEmpty()) {
        TeacherCommissionMember tcm;
        tcm.printHeader();
        
        Deque<Human*> temp;
        while (!deque.isEmpty()) {
            Human* human = deque.peekFirst();
            deque.popFront();
            human->printTable();
            temp.pushBack(human);
        }

        while (!temp.isEmpty()) {
            Human* human = temp.peekLast();
            temp.popBack();
            deque.pushFront(human);
        }
    }
}

void searchInDeque(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    string searchOptions[5] = {"1. Search by Last Name", "2. Search by First Name", "3. Search by Middle Name", "4. Search by Birthday", "5. Search by Full Match (all fields)"};
    drawMenu("Search Options", searchOptions, 5);
    int choice = getChoice(5);

    string searchString;
    Date searchDate;
    Date defaultDate(1, 1, 1900);
    
    UniversityTeacher* searchObj = new UniversityTeacher("", "", "", defaultDate, "", "", "");

    if (choice == 1) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter last name to search (English only): ");
                searchObj->setLastName(searchString);
                Human::setSearchMode(LAST_NAME);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 2) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter first name to search (English only): ");
                searchObj->setFirstName(searchString);
                Human::setSearchMode(FIRST_NAME);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 3) {
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter middle name to search (English only): ");
                searchObj->setMiddleName(searchString);
                Human::setSearchMode(MIDDLE_NAME);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else if (choice == 4) {
        bool success = false;
        while (!success) {
            try {
                safeInputDate(cin, searchDate, "DD/MM/YYYY", "Enter birthday to search: ");
                searchObj->setBirthday(searchDate);
                Human::setSearchMode(BIRTH_YEAR);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    } else { 
        cout << "Enter criteria for Full Match:" << endl;
        
        bool success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter last name (English only): ");
                searchObj->setLastName(searchString);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        
        success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter first name (English only): ");
                searchObj->setFirstName(searchString);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        
        success = false;
        while (!success) {
            try {
                safeInputString(cin, searchString, Language::ENGLISH, "Enter middle name (English only): ");
                searchObj->setMiddleName(searchString);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        
        success = false;
        while (!success) {
            try {
                safeInputDate(cin, searchDate, "DD/MM/YYYY", "Enter birthday: ");
                searchObj->setBirthday(searchDate);
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        
        Human::setSearchMode(FULL_MATCH); 
    }

    Deque<Human*> searchResults = deque.find(searchObj);
    
    Human::setSearchMode(FULL_MATCH); 
    delete searchObj;
    
    if (searchResults.isEmpty()) {
        cout << "No matches found." << endl;
    } else {
        cout << "Search results (" << searchResults.size() << " found):" << endl;
        printDeque(searchResults); 
    }
}

void clearDeque(Deque<Human*>& deque) {
    while (!deque.isEmpty()) {
        delete deque.peekFirst();
        deque.popFront();
    }
    cout << "Deque cleared." << endl;
}

void sortDequeByField(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty. Nothing to sort." << endl;
        return;
    }
    string sortOptions[4] = {"1. Sort by Last Name", "2. Sort by First Name", "3. Sort by Middle Name", "4. Sort by Birth Year"};
    drawMenu("Sort Options", sortOptions, 4);
    int choice = getChoice(4); 

    if (choice == 1) {
        Human::setSearchMode(LAST_NAME);
        cout << "Sorting by Last Name..." << endl;
    } else if (choice == 2) {
        Human::setSearchMode(FIRST_NAME);
        cout << "Sorting by First Name..." << endl;
    } else if (choice == 3) {
        Human::setSearchMode(MIDDLE_NAME);
        cout << "Sorting by Middle Name..." << endl;
    } else if (choice == 4) {
        Human::setSearchMode(BIRTH_YEAR);
        cout << "Sorting by Birth Year..." << endl;
    } else {
        cout << "Invalid choice. Aborting sort." << endl;
        return;
    }

    deque.sort();
    
    Human::setSearchMode(LAST_NAME); 
    
    cout << "Deque sorted successfully." << endl;
    printDeque(deque);
}

void run(){
    Deque<Human*> myDeque;
    int choice;
    string mainMenuOptions[8] = {
        "1. Add Object",
        "2. Remove Object", 
        "3. Modify Object",
        "4. Peek Object",
        "5. Print Deque",
        "6. Search",
        "7. Sort",
        "8. Exit"
    };
    
    do {
        drawMenu("Main Menu", mainMenuOptions, 8);
        choice = getChoice(8);
        
        switch (choice) {
            case 1: addObject(myDeque); break;
            case 2: removeObject(myDeque); break;
            case 3: modifyObject(myDeque); break;
            case 4: peekObject(myDeque); break;
            case 5: printDeque(myDeque); break;
            case 6: searchInDeque(myDeque); break;
            case 7: sortDequeByField(myDeque); break;
            case 8: clearDeque(myDeque); break;
        }
    } while (choice != 8);
}

int main() {
    string restart;
    do{
        run();
        bool success = false;
        while (!success) {
            try {
                safeInputText(cin, restart, "Do u wana repeate this task(y/n) y - yes, n - no: ");
                success = true;
            } catch (const InputException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }while(restart != "n" && restart != "N");
    cout << "Exiting ...";
    return 0;
}