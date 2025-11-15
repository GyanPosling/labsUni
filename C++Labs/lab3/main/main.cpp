#include <iostream>
#include <iomanip>
#include <limits>
#include "TeacherCommissionMember.hpp"

using namespace std;

const int MAX_OBJECTS = 10;
TeacherCommissionMember objects[MAX_OBJECTS];
int objectCount = 0;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    const int width = 60;

    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;

    string title = "TEACHER COMMISSION MEMBER MANAGEMENT SYSTEM";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title << setw(width - 2 - padding - (int)title.length()) << " " << "|" << endl;

    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;

    cout << " |  1. Add Teacher Commission Member" << setw(width - 35) << " " << "|" << endl;
    cout << " |  2. Show All" << setw(width - 16) << " " << "|" << endl;
    cout << " |  3. Edit Teacher Commission Member" << setw(width - 36) << " " << "|" << endl;
    cout << " |  4. Delete Teacher Commission Member" << setw(width - 38) << " " << "|" << endl;
    cout << " |  0. Exit" << setw(width - 13) << " " << "|" << endl;
    
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " Select option: ";
}

void addObject() {
    if (objectCount >= MAX_OBJECTS) {
        cout << "Cannot add more objects! Maximum reached.\n";
        return;
    }
    
    TeacherCommissionMember newObject;
    cout << "Enter Teacher Commission Member data:\n";
    cin >> newObject;
    
    objects[objectCount] = newObject;
    objectCount++;
    cout << "Teacher Commission Member added successfully!\n";
}

void showAll() {
    cout << "\n" << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    cout << "                 TEACHER COMMISSION MEMBERS" << endl;
    cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    
    if (objectCount > 0) {
        objects[0].printHeader();
        cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
        for (int i = 0; i < objectCount; i++) {
            objects[i].printTable();
        }
        cout << setfill('=') << setw(120) << "=" << setfill(' ') << endl;
    } else {
        cout << "No Teacher Commission Members found." << endl;
    }
}

void editObject() {
    if (objectCount == 0) {
        cout << "No objects to edit.\n";
        return;
    }
    
    cout << "\nAvailable Teacher Commission Members:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << objects[i] << endl;
    }
    
    cout << "Select object to edit: ";
    int index;
    cin >> index;
    clearInput();
    
    if (index < 1 || index > objectCount) {
        cout << "Invalid selection.\n";
        return;
    }
    
    TeacherCommissionMember& obj = objects[index - 1];
    
    cout << "Current data: " << obj << endl;
    cout << "Enter new data:\n";
    cin >> obj;
    
    cout << "Object updated successfully!\n";
}

void deleteObject() {
    if (objectCount == 0) {
        cout << "No objects to delete.\n";
        return;
    }
    
    cout << "\nAvailable Teacher Commission Members:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << objects[i] << endl;
    }
    
    cout << "Select object to delete: ";
    int index;
    cin >> index;
    
    if (index < 1 || index > objectCount) {
        cout << "Invalid selection.\n";
        return;
    }
    
    cout << "Deleting: " << objects[index - 1] << endl;
    
    for (int i = index - 1; i < objectCount - 1; i++) {
        objects[i] = objects[i + 1];
    }
    objectCount--;
    
    cout << "Object deleted successfully!\n";
}

int main() {
    int choice;
    
    do {
        printMenu();
        cin >> choice;
        clearInput();
        
        switch (choice) {
            case 1:
                addObject();
                break;
            case 2:
                showAll();
                break;
            case 3:
                editObject();
                break;
            case 4:
                deleteObject();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
        
        cout << "\nPress Enter to continue...";
        clearInput();
        
    } while (choice != 0);
    
    return 0;
}