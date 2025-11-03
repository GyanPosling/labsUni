#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "../models/include/Human.hpp"
#include "../models/include/Teacher.hpp"
#include "../models/include/CommissionMember.hpp"
#include "../models/include/TeacherCommissionMember.hpp"
#include "../templates/include/Deque.hpp"
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
    cout << "Enter choice: ";
    cin >> choice;
    while (choice < 1 || choice > max) {
        cout << "Invalid. Enter choice: ";
        cin >> choice;
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
    int num;
    string options[4] = {"1. First Name", "2. Last Name", "3. Middle Name", "4. Birth Year"};
    drawMenu("Select Human Field", options, 4);
    int choice = getChoice(4);
    if (choice == 1) {
        cout << "New first name: ";
        cin >> str;
        human->setFirstName(str);
    } else if (choice == 2) {
        cout << "New last name: ";
        cin >> str;
        human->setLastName(str);
    } else if (choice == 3) {
        cout << "New middle name: ";
        cin >> str;
        human->setMiddleName(str);
    } else {
        cout << "New birth year: ";
        cin >> num;
        human->setBirthYear(num);
    }
}

void updateTeacherFields(UniversityTeacher* teacher) {
    string str;
    int num;
    string options[5] = {"1. Position", "2. Degree", "3. Specialty", "4. Add Scientific Work", "5. Replace All Scientific Works"};
    drawMenu("Select Teacher Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        cout << "New position: ";
        cin >> str;
        teacher->setPosition(str);
    } else if (choice == 2) {
        cout << "New degree: ";
        cin >> str;
        teacher->setAcademicDegree(str);
    } else if (choice == 3) {
        cout << "New specialty: ";
        cin >> str;
        teacher->setSpecialty(str);
    } else if (choice == 4) {
        cout << "New scientific work: ";
        cin >> str;
        teacher->addScientificWork(str);
    } else {
        cout << "Enter number of scientific works (0-5): ";
        cin >> num;
        if (num > 5) num = 5;
        for (int i = 0; i < num; i++) {
            cout << "Scientific work " << i+1 << ": ";
            cin >> str;
            teacher->setScientificWork(i, str);
        }
    }
}

void updateCommissionFields(CommissionMember* commissionMember) {
    string str;
    int num;
    string options[5] = {"1. Commission Name", "2. Appointment Year", "3. Certificate Number", "4. Add Autobiography", "5. Replace All Autobiography"};
    drawMenu("Select Commission Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        cout << "New commission name: ";
        cin >> str;
        commissionMember->setCommissionName(str);
    } else if (choice == 2) {
        cout << "New appointment year: ";
        cin >> num;
        commissionMember->setAppointmentYear(num);
    } else if (choice == 3) {
        cout << "New certificate number: ";
        cin >> str;
        commissionMember->setCertificateNumber(str);
    } else if (choice == 4) {
        cout << "New autobiography: ";
        cin >> str;
        commissionMember->addAutobiography(str);
    } else {
        cout << "Enter number of autobiography (0-10): ";
        cin >> num;
        if (num > 10) num = 10;
        for (int i = 0; i < num; i++) {
            cout << "Autobiography " << i+1 << ": ";
            cin >> str;
            commissionMember->setAutobiography(i, str);
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
        cout << "New commission work: ";
        cin >> str;
        teacherCommissionMember->addCommissionWork(str);
    } else {
        cout << "Enter number of commission works (0-5): ";
        cin >> num;
        if (num > 5) num = 5;
        for (int i = 0; i < num; i++) {
            cout << "Commission work " << i+1 << ": ";
            cin >> str;
            teacherCommissionMember->setCommissionWork(i, str);
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

    string searchOptions[3] = {"1. Search by Last Name", "2. Search by Birth Year", "3. Search by Position"};
    drawMenu("Search Options", searchOptions, 3);
    int choice = getChoice(3);

    string searchString;
    int searchYear;
    
    if (choice == 1) {
        cout << "Enter last name to search: ";
        cin >> searchString;
    } else if (choice == 2) {
        cout << "Enter birth year to search: ";
        cin >> searchYear;
    } else if (choice == 3) {
        cout << "Enter position to search: ";
        cin >> searchString;
    }

    Deque<Human*> searchResults;
    Deque<Human*> temp;

    while (!deque.isEmpty()) {
        Human* human = deque.peekFirst();
        deque.popFront();
        temp.pushBack(human);

        bool match = false;
        if (choice == 1) {
            match = (human->getLastName() == searchString);
        } else if (choice == 2) {
            match = (human->getBirthYear() == searchYear);
        } else if (choice == 3) {
            if (UniversityTeacher* teacher = dynamic_cast<UniversityTeacher*>(human)) {
                match = (teacher->getPosition() == searchString);
            }
        }

        if (match) {
            searchResults.pushBack(human);
        }
    }

    while (!temp.isEmpty()) {
        Human* human = temp.peekFirst();
        temp.popFront();
        deque.pushBack(human);
    }

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

void sortDeque(Deque<Human*>& deque) {
    deque.sort();
    cout << "Deque sorted." << endl;
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
            case 7: sortDeque(myDeque); break;
            case 8: clearDeque(myDeque); break;
        }
    } while (choice != 8);
}

int main() {
    char restart;
    do{
        run();
        cout << "Do u wana repeate this task(y/n) y - yes, n - no" << endl;
        cin >> restart;
    }while(restart != 'n');
    cout << "Exiting ...";
    return 0;
}