#include <iostream>
#include <string>
#include <iomanip>
#include "../models/include/Human.hpp"
#include "../models/include/Teacher.hpp"
#include "../models/include/CommissionMember.hpp"
#include "../models/include/TeacherCommissionMember.hpp"
#include "../templates/include/Deque.hpp"
using namespace std;

void printObjectDetails(const Human* h, const string& label = "") {
    if (!label.empty()) {
        cout << "=== " << label << " ===" << endl;
    }
    cout << "Last Name: " << h->getLastName() << endl;
    cout << "First Name: " << h->getFirstName() << endl;
    cout << "Middle Name: " << h->getMiddleName() << endl;
    cout << "Birth Year: " << h->getBirthYear() << endl;

    UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(const_cast<Human*>(h));
    if (t) {
        cout << "Position: " << t->getPosition() << endl;
        cout << "Academic Degree: " << t->getAcademicDegree() << endl;
        cout << "Specialty: " << t->getSpecialty() << endl;
        cout << "Scientific Works (" << t->getScientificWorksCount() << "): ";
        for (int i = 0; i < t->getScientificWorksCount(); ++i) {
            if (i > 0) cout << ", ";
            cout << t->getScientificWork(i);
        }
        cout << endl;
    }

    CommissionMember* c = dynamic_cast<CommissionMember*>(const_cast<Human*>(h));
    if (c) {
        cout << "Commission Name: " << c->getCommissionName() << endl;
        cout << "Appointment Year: " << c->getAppointmentYear() << endl;
        cout << "Certificate Number: " << c->getCertificateNumber() << endl;
        cout << "Autobiography (" << c->getAutobiographyCount() << "): ";
        for (int i = 0; i < c->getAutobiographyCount(); ++i) {
            if (i > 0) cout << ", ";
            cout << c->getAutobiography(i);
        }
        cout << endl;
    }

    TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(const_cast<Human*>(h));
    if (tcm) {
        cout << "Commission Works (" << tcm->getCommissionWorksCount() << "): ";
        for (int i = 0; i < tcm->getCommissionWorksCount(); ++i) {
            if (i > 0) cout << ", ";
            cout << tcm->getCommissionWork(i);
        }
        cout << endl;
    }
    cout << "-------------------" << endl;
}

void printDeque(Deque<Human*>& dq) {
    if (dq.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    Deque<Human*> temp;
    int index = 1;
    cout << "===== Deque Contents (Front to Back) =====" << endl;
    while (!dq.isEmpty()) {
        Human* h = dq.peekFirst();
        string label = "Object " + to_string(index);
        if (index == 1) label += " (Front)";
        printObjectDetails(h, label);
        dq.popFront();
        temp.pushBack(h);
        index++;
    }
    // Restore original Deque
    while (!temp.isEmpty()) {
        Human* h = temp.peekLast();
        temp.popBack();
        dq.pushFront(h);
    }
    cout << "===== End of Deque =====" << endl;
}

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

void addObject(Deque<Human*>& dq, bool front) {
    string options[3] = {"1. Teacher", "2. Commission Member", "3. Teacher Commission Member"};
    drawMenu("Select Type to Add", options, 3);
    int choice = getChoice(3);
    Human* obj = nullptr;
    if (choice == 1) {
        UniversityTeacher* t = new UniversityTeacher();
        cin >> *t;
        obj = t;
    } else if (choice == 2) {
        CommissionMember* c = new CommissionMember();
        cin >> *c;
        obj = c;
    } else {
        TeacherCommissionMember* tcm = new TeacherCommissionMember();
        cin >> *tcm;
        obj = tcm;
    }
    if (front) {
        dq.pushFront(obj);
    } else {
        dq.pushBack(obj);
    }
}

void updateHumanFields(Human* h) {
    string str;
    int num;
    string options[4] = {"1. First Name", "2. Last Name", "3. Middle Name", "4. Birth Year"};
    drawMenu("Select Human Field", options, 4);
    int choice = getChoice(4);
    if (choice == 1) {
        cout << "New first name: ";
        cin >> str;
        h->setFirstName(str);
    } else if (choice == 2) {
        cout << "New last name: ";
        cin >> str;
        h->setLastName(str);
    } else if (choice == 3) {
        cout << "New middle name: ";
        cin >> str;
        h->setMiddleName(str);
    } else {
        cout << "New birth year: ";
        cin >> num;
        h->setBirthYear(num);
    }
}

void updateTeacherFields(UniversityTeacher* t) {
    string str;
    int num;
    string options[5] = {"1. Position", "2. Degree", "3. Specialty", "4. Add Scientific Work", "5. Replace All Scientific Works"};
    drawMenu("Select Teacher Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        cout << "New position: ";
        cin >> str;
        t->setPosition(str);
    } else if (choice == 2) {
        cout << "New degree: ";
        cin >> str;
        t->setAcademicDegree(str);
    } else if (choice == 3) {
        cout << "New specialty: ";
        cin >> str;
        t->setSpecialty(str);
    } else if (choice == 4) {
        cout << "New scientific work: ";
        cin >> str;
        t->addScientificWork(str);
    } else {
        cout << "Enter number of scientific works (0-5): ";
        cin >> num;
        if (num > 5) num = 5;
        for (int i = 0; i < num; i++) {
            cout << "Scientific work " << i+1 << ": ";
            cin >> str;
            t->setScientificWork(i, str);
        }
    }
}

void updateCommissionFields(CommissionMember* c) {
    string str;
    int num;
    string options[5] = {"1. Commission Name", "2. Appointment Year", "3. Certificate Number", "4. Add Autobiography", "5. Replace All Autobiography"};
    drawMenu("Select Commission Field", options, 5);
    int choice = getChoice(5);
    if (choice == 1) {
        cout << "New commission name: ";
        cin >> str;
        c->setCommissionName(str);
    } else if (choice == 2) {
        cout << "New appointment year: ";
        cin >> num;
        c->setAppointmentYear(num);
    } else if (choice == 3) {
        cout << "New certificate number: ";
        cin >> str;
        c->setCertificateNumber(str);
    } else if (choice == 4) {
        cout << "New autobiography: ";
        cin >> str;
        c->addAutobiography(str);
    } else {
        cout << "Enter number of autobiography (0-10): ";
        cin >> num;
        if (num > 10) num = 10;
        for (int i = 0; i < num; i++) {
            cout << "Autobiography " << i+1 << ": ";
            cin >> str;
            c->setAutobiography(i, str);
        }
    }
}

void updateTCMExtraFields(TeacherCommissionMember* tcm) {
    string str;
    int num;
    string options[2] = {"1. Add Commission Work", "2. Replace All Commission Works"};
    drawMenu("Select TCM Extra Field", options, 2);
    int choice = getChoice(2);
    if (choice == 1) {
        cout << "New commission work: ";
        cin >> str;
        tcm->addCommissionWork(str);
    } else {
        cout << "Enter number of commission works (0-5): ";
        cin >> num;
        if (num > 5) num = 5;
        for (int i = 0; i < num; i++) {
            cout << "Commission work " << i+1 << ": ";
            cin >> str;
            tcm->setCommissionWork(i, str);
        }
    }
}

void modifyObject(Human* h) {
    string modifyOptions[2] = {"1. Change All", "2. Change Specific Field"};
    drawMenu("Modify Options", modifyOptions, 2);
    int choice = getChoice(2);
    if (choice == 1) {
        cin >> *h;
        return;
    }
    TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(h);
    UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(h);
    CommissionMember* c = dynamic_cast<CommissionMember*>(h);
    int numFieldOptions = 1;
    string fieldOptions[4];
    fieldOptions[0] = "1. Human Fields";
    if (t) {
        fieldOptions[numFieldOptions++] = "2. Teacher Fields";
    }
    if (c) {
        fieldOptions[numFieldOptions++] = "3. Commission Fields";
    }
    if (tcm) {
        fieldOptions[numFieldOptions++] = "4. TCM Extra Fields";
    }
    drawMenu("Select Field Category", fieldOptions, numFieldOptions);
    choice = getChoice(numFieldOptions);
    if (choice == 1) {
        updateHumanFields(h);
    } else if (choice == 2 && t) {
        if (tcm && numFieldOptions > 3) {
            if (choice == 2) updateTeacherFields(t);
            else if (choice == 3) updateCommissionFields(c);
            else if (choice == 4) updateTCMExtraFields(tcm);
        } else if (tcm) {
            if (choice == 2) updateTeacherFields(t);
            else if (choice == 3) updateCommissionFields(c);
        } else {
            updateTeacherFields(t);
        }
    } else if (choice == 3 && c && !tcm) {
        updateCommissionFields(c);
    }
}

void modifyFirstOrLast(Deque<Human*>& dq, bool first) {
    if (dq.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    Human* h = first ? dq.peekFirst() : dq.peekLast();
    modifyObject(h);
}

void peekFirstOrLast(Deque<Human*>& dq, bool first) {
    if (dq.isEmpty()) {
        cout << "Empty" << endl;
        return;
    }
    Human* h = first ? dq.peekFirst() : dq.peekLast();
    printObjectDetails(h, (first ? "First Object" : "Last Object"));
}

void handleMenuChoice(int choice, Deque<Human*>& myDeque) {
    switch (choice) {
        case 1: addObject(myDeque, true); break;
        case 2: addObject(myDeque, false); break;
        case 3: if (!myDeque.isEmpty()) { delete myDeque.peekFirst(); myDeque.popFront(); } else cout << "Empty" << endl; break;
        case 4: if (!myDeque.isEmpty()) { delete myDeque.peekLast(); myDeque.popBack(); } else cout << "Empty" << endl; break;
        case 5: modifyFirstOrLast(myDeque, true); break;
        case 6: modifyFirstOrLast(myDeque, false); break;
        case 7: peekFirstOrLast(myDeque, true); break;
        case 8: peekFirstOrLast(myDeque, false); break;
        case 9: printDeque(myDeque); break;
        case 10: while (!myDeque.isEmpty()) { delete myDeque.peekFirst(); myDeque.popFront(); } break;
    }
}

int main() {
    Deque<Human*> myDeque;
    int choice;
    string menuOptions[11] = {
        "1. Push Front", "2. Push Back", "3. Pop Front", "4. Pop Back",
        "5. Modify First", "6. Modify Last", "7. Peek First",
        "8. Peek Last", "9. Print Deque", "10. Clear Deque", "11. Exit"
    };
    do {
        drawMenu("Deque Menu", menuOptions, 11);
        choice = getChoice(11);
        if (choice != 11) {
            handleMenuChoice(choice, myDeque);
        }
    } while (choice != 11);
    while (!myDeque.isEmpty()) { delete myDeque.peekFirst(); myDeque.popFront(); }
    return 0;
}