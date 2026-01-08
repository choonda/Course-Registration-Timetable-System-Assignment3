#include "SystemManager.h"
#include "Student.h"
#include <iostream>
#include <limits>

int main() {
    SystemManager system;
    Student student;

    // load data
    system.loadCoursesFromFile("courses.txt");

    int choice;
    do {
        std::cout << "\n===== MAIN MENU =====\n";
        std::cout << "1. Admin Login\n";
        std::cout << "2. Student Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (system.adminLogin()) {
                    system.adminMenu();
                } else {
                    std::cout << "Admin login failed. Returning to main menu.\n";
                }
                break;
            case 2: {
                // Ask student for ID and name at login
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string sid, sname;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, sid);
                std::cout << "Enter Student Name: ";
                std::getline(std::cin, sname);
                student.setStudentID(sid);
                student.setStudentName(sname);
                std::cout << "Welcome, " << student.getStudentName() << " (" << student.getStudentID() << ")\n";
                system.studentMenu(student);
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
