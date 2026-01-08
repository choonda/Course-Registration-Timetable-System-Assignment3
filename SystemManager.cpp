#include "SystemManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

SystemManager::SystemManager()
    : head(nullptr), totalCourses(0), adminPassword("admin123") {}

SystemManager::~SystemManager() {
    CourseNode* current = head;
    while (current != nullptr) {
        CourseNode* next = current->next;
        delete current;
        current = next;
    }
}

bool SystemManager::adminLogin() {
    std::string pass;
    std::cout << "Enter admin password: ";
    std::cin >> pass;

    if (pass == adminPassword) {
        std::cout << "Login successful!\n";
        return true;
    } else {
        std::cout << "Incorrect password!\n";
        return false;
    }
}
    
void SystemManager::loadCoursesFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file '" << filename << "'!" << std::endl;
        return;
    }

    std::string line;
    while (head != nullptr) {
        CourseNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    totalCourses = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Course c;
        std::stringstream ss(line);

        std::string creditStr;
        std::string tmp;
        if (!std::getline(ss, tmp, '|')) continue; c.setCourseCode(tmp);
        if (!std::getline(ss, tmp, '|')) continue; c.setCourseName(tmp);
        if (!std::getline(ss, creditStr, '|')) continue;
        try {
            c.setCreditHour(std::stoi(creditStr));
        } catch (...) {
            c.setCreditHour(0);
        }
        if (!std::getline(ss, tmp, '|')) continue; c.setLecturer(tmp);
        if (!std::getline(ss, tmp, '|')) continue; c.setDay(tmp);
        if (!std::getline(ss, tmp, '|')) continue; c.setTime(tmp);
        if (!std::getline(ss, tmp)) c.setVenue(""); else c.setVenue(tmp);

        if (!c.getCourseCode().empty()) {
            CourseNode* newNode = new CourseNode;
            newNode->course = c;
            newNode->next = nullptr;
            
            if (head == nullptr) {
                head = newNode;
            } else {
                CourseNode* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            totalCourses++;
        }
    }

    file.close();
    std::cout << "Courses loaded: " << totalCourses << std::endl;
}

void SystemManager::displayAllCoursesSortedByCourseCode() const {
    if (totalCourses == 0) { std::cout << "No courses available\n"; return; }

    Course list[100];
    int listCount = 0;
    CourseNode* current = head;
    while (current != nullptr && listCount < 100) {
        list[listCount++] = current->course;
        current = current->next;
    }

    selectionSortCourses(list, listCount, "code", true);

    std::cout << "\n===== COURSE LIST (sorted by course code) =====\n";
    std::cout << std::left
              << std::setw(10) << "Code" << " | "
              << std::setw(30) << "Name" << " | "
              << std::setw(5)  << "CH"   << " | "
              << std::setw(18) << "Lecturer" << " | "
              << std::setw(10) << "Day"  << " | "
              << std::setw(13) << "Time" << " | "
              << std::setw(8)  << "Venue" << std::endl;
    for (int i = 0; i < listCount; ++i) list[i].display();
}

// Display all courses sorted by lecturer name (bubble sort)
void SystemManager::displayAllCoursesSortedByLecturerName() const {
    if (totalCourses == 0) { std::cout << "No courses available\n"; return; }
    Course list[100];
    int listCount = 0;
    CourseNode* current = head;
    while (current != nullptr && listCount < 100) {
        list[listCount++] = current->course;
        current = current->next;
    }
    bubbleSortCourses(list, listCount, "lecturer", true);

    std::cout << "\n===== COURSE LIST (sorted by lecturer) =====\n";
    std::cout << std::left
              << std::setw(10) << "Code" << " | "
              << std::setw(30) << "Name" << " | "
              << std::setw(5)  << "CH"   << " | "
              << std::setw(18) << "Lecturer" << " | "
              << std::setw(10) << "Day"  << " | "
              << std::setw(13) << "Time" << " | "
              << std::setw(8)  << "Venue" << std::endl;
    for (int i = 0; i < listCount; ++i) list[i].display();
}

// Display all courses sorted by credit hour (insertion sort)
void SystemManager::displayAllCoursesSortedByCreditHour() const {
    if (totalCourses == 0) { std::cout << "No courses available\n"; return; }
    Course list[100];
    int listCount = 0;
    CourseNode* current = head;
    while (current != nullptr && listCount < 100) {
        list[listCount++] = current->course;
        current = current->next;
    }
    insertionSortCourses(list, listCount, "credit", true);

    std::cout << "\n===== COURSE LIST (sorted by credit hour) =====\n";
    std::cout << std::left
              << std::setw(10) << "Code" << " | "
              << std::setw(30) << "Name" << " | "
              << std::setw(5)  << "CH"   << " | "
              << std::setw(18) << "Lecturer" << " | "
              << std::setw(10) << "Day"  << " | "
              << std::setw(13) << "Time" << " | "
              << std::setw(8)  << "Venue" << std::endl;
    for (int i = 0; i < listCount; ++i) list[i].display();
}

int SystemManager::searchCourseByCode(const std::string &code) const {
    CourseNode* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->course.getCourseCode() == code) return index;
        current = current->next;
        index++;
    }
    return -1;
}

int SystemManager::searchCourseByCourseName(const std::string &name) const {
    std::string target;
    target.reserve(name.size());
    for (char ch : name) target.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));

    CourseNode* current = head;
    int index = 0;
    while (current != nullptr) {
        std::string courseName = current->course.getCourseName();
        std::string lowerCourse;
        lowerCourse.reserve(courseName.size());
        for (char ch : courseName) lowerCourse.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        if (lowerCourse.find(target) != std::string::npos) return index; // return first match
        current = current->next;
        index++;
    }
    return -1;
}

void SystemManager::manageTimetable() {
    std::string code;
    std::cout << "Enter course code to manage timetable: ";
    std::cin >> code;

    CourseNode* current = head;
    while (current != nullptr) {
        if (current->course.getCourseCode() == code) break;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Course not found!\n";
        return;
    }

    Course &c = current->course;

    std::cout << "\nCurrent Timetable for " << code << ":\n";
    std::cout << "Day: " << c.getDay()
              << " | Time: " << c.getTime()
              << " | Venue: " << c.getVenue() << std::endl;

    std::cout << "Enter new day (or press Enter to keep): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string newDay;
    std::getline(std::cin, newDay);
    if (!newDay.empty()) c.setDay(newDay);

    std::cout << "Enter new time (or press Enter to keep): ";
    std::string newTime;
    std::getline(std::cin, newTime);
    if (!newTime.empty()) c.setTime(newTime);

    std::cout << "Enter new venue (or press Enter to keep): ";
    std::string newVenue;
    std::getline(std::cin, newVenue);
    if (!newVenue.empty()) c.setVenue(newVenue);

    std::cout << "Timetable updated successfully!\n";
    saveCoursesToFile();
}

// Function 1: Student adds themselves to the queue (Enqueue)
void SystemManager::studentApplyForCourse(Student &s) {
    std::string code;
    std::cout << "Enter Course Code to apply for: ";
    std::cin >> code;

    // Check if course exists in the system
    if (searchCourseByCode(code) == -1) {
        std::cout << "Error: Course " << code << " does not exist.\n";
        return;
    }

    // Check if student is already registered locally
    if (s.isRegistered(code)) {
        std::cout << "You are already registered for this course.\n";
        return;
    }

    pendingQueue.enqueue(s.getStudentID(), code);
    std::cout << "Application for " << code << " submitted to the waiting list.\n";
}

// Function 2: Admin approves the oldest request (Dequeue)
void SystemManager::adminProcessNextRequest() {
    if (pendingQueue.isEmpty()) { 
        std::cout << "No pending requests to process.\n";
        return;
    }

    Request req = pendingQueue.dequeue(); 
    std::cout << "Processing: Student [" << req.studentID 
              << "] for Course [" << req.courseCode << "]\n";
    
    std::cout << "Status: REQUEST APPROVED.\n";
    
    std::ofstream regFile("registrations.txt", std::ios::app);
    if (regFile.is_open()) {
        regFile << req.studentID << "|" << req.courseCode << "\n";
        regFile.close();
        std::cout << "Registration saved to system.\n";
    } else {
        std::cout << "Error: Could not save registration!\n";
    }
}

void SystemManager::loadStudentRegistrations(Student &s) {
    std::ifstream regFile("registrations.txt");
    if (!regFile.is_open()) return; 

    std::string line;
    while (std::getline(regFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string sid, code;
        if (std::getline(ss, sid, '|') && std::getline(ss, code)) {
            if (sid == s.getStudentID()) {
                if (!s.isRegistered(code)) {
                    s.registerCourse(code);
                }
            }
        }
    }
    regFile.close();
}

// Function 3: Admin views the current waiting list (Traverse)
void SystemManager::adminViewPendingRequests() const {
    std::cout << "\n--- CURRENT REGISTRATION QUEUE ---\n";
    pendingQueue.displayQueue(); 
}

// Function 4: Admin wipes the queue (Destroy)
void SystemManager::adminClearAllRequests() {
    char confirm;
    std::cout << "Are you sure you want to clear all pending requests? (y/n): ";
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        pendingQueue.clearQueue(); 
        std::cout << "Queue has been emptied.\n";
    }
}

void SystemManager::adminMenu() {
    int choice;
    do {
        std::cout << "\n===== ADMIN MENU =====\n";
        std::cout << "1. View courses sorted by course code\n";
        std::cout << "2. View courses sorted by lecturer name\n";
        std::cout << "3. View courses sorted by credit hour\n";
        std::cout << "4. Search Course\n";
        std::cout << "5. Manage Timetable\n";
        std::cout << "6. Add Course\n";
        std::cout << "7. Delete Course\n";
        std::cout << "8. View Pending Queue\n";
        std::cout << "9. Process Next Request\n";
        std::cout << "10. Clear All Requests\n";
        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: displayAllCoursesSortedByCourseCode(); break;
            case 2: displayAllCoursesSortedByLecturerName(); break;
            case 3: displayAllCoursesSortedByCreditHour(); break;
            case 4: {
                {
                    std::cout << "Search by: 1) Code  2) Course name\n";
                    int sub;
                    std::cout << "Choice: "; std::cin >> sub;
                    if (sub == 1) {
                        std::string code;
                        std::cout << "Enter course code: ";
                        std::cin >> code;
                        int idx = searchCourseByCode(code);
                        if (idx != -1) getCourseAt(idx).display();
                        else std::cout << "Course not found!\n";
                    } else if (sub == 2) {
                        std::string name;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Enter course name (or part of it): ";
                        std::getline(std::cin, name);
                        int idx = searchCourseByCourseName(name);
                        if (idx != -1) getCourseAt(idx).display();
                        else std::cout << "Course not found!\n";
                    } else std::cout << "Invalid choice." << std::endl;
                }
                break;
            }
            case 5: manageTimetable(); break;
            case 6: addCourse(); break;
            case 7: deleteCourse(); break;
            case 8: adminViewPendingRequests(); break;
            case 9: adminProcessNextRequest(); break;
            case 10: adminClearAllRequests(); break;
            case 0: break;
            default: std::cout << "Invalid choice!\n"; break;
        }
    } while (choice != 0);
}

void SystemManager::studentMenu(Student &s) {
    loadStudentRegistrations(s);

    int choice;
    do {
        std::cout << "\n===== STUDENT MENU =====\n";
        std::cout << "1. Apply for Course (Add to Queue)\n";
        std::cout << "2. Drop Course\n";
        std::cout << "3. View Timetable sorted by course code\n";
        std::cout << "4. View Timetable sorted by Lecturer name\n";
        std::cout << "5. View Timetable sorted by credit hour\n";
        std::cout << "6. View All Courses\n";
        std::cout << "7. Search Course\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: {
                std::string code;
                std::cout << "Course Code: ";
                std::cin >> code;
                if (searchCourseByCode(code) == -1) {
                    std::cout << "Course does not exist!\n";
                } else {
                    pendingQueue.enqueue(s.getStudentID(), code);
                    std::cout << "Application submitted to queue.\n";
                }
                break;
            }
            case 2: {
                std::string code;
                std::cout << "Course Code: ";
                std::cin >> code;
                s.dropCourse(code);
                break;
            }
            case 3:
                displayTimetableSortedByCourseCode(s);
                break;
            case 4:
                displayTimetableSortedByLecturerName(s);
                break;
            case 5:
                displayTimetableSortedByCreditHour(s);
                break;
            case 6:
                studentViewAllCourses();
                break;
            case 7: {
                std::cout << "Search by: 1) Code  2) Course name\n";
                int sub;
                std::cout << "Choice: "; 
                std::cin >> sub;
                if (sub == 1) studentSearchCourseByCode();
                else if (sub == 2) studentSearchCourseByCourseName();
                else std::cout << "Invalid choice." << std::endl;
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    } while (choice != 0);
}

void SystemManager::studentViewAllCourses() const {
    // Uses the same display as admin but kept separate for clarity
    // Students see courses sorted by course code by default
    displayAllCoursesSortedByCourseCode();
}

void SystemManager::studentSearchCourseByCode() const {
    std::string code;
    std::cout << "Enter course code to search: ";
    std::cin >> code;

    int index = searchCourseByCode(code);
    if (index == -1) {
        std::cout << "Course not found!" << std::endl;
    } else {
        std::cout << "Course details:\n";
        std::cout << std::left
                  << std::setw(10) << "Code" << " | "
                  << std::setw(30) << "Name" << " | "
                  << std::setw(5)  << "CH"   << " | "
                  << std::setw(18) << "Lecturer" << " | "
                  << std::setw(10) << "Day"  << " | "
                  << std::setw(13) << "Time" << " | "
                  << std::setw(8)  << "Venue" << std::endl;
        getCourseAt(index).display();
    }
}

void SystemManager::studentSearchCourseByCourseName() const {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name;
    std::cout << "Enter course name (or part of it) to search: ";
    std::getline(std::cin, name);

    std::string target;
    target.reserve(name.size());
    for (char ch : name) target.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));

    bool found = false;
    std::cout << "Search results:\n";
    std::cout << std::left
              << std::setw(10) << "Code" << " | "
              << std::setw(30) << "Name" << " | "
              << std::setw(5)  << "CH"   << " | "
              << std::setw(18) << "Lecturer" << " | "
              << std::setw(10) << "Day"  << " | "
              << std::setw(13) << "Time" << " | "
              << std::setw(8)  << "Venue" << std::endl;

    CourseNode* current = head;
    while (current != nullptr) {
        std::string courseName = current->course.getCourseName();
        std::string lowerCourse;
        lowerCourse.reserve(courseName.size());
        for (char ch : courseName) lowerCourse.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        if (lowerCourse.find(target) != std::string::npos) {
            current->course.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) std::cout << "No matching courses found." << std::endl;
}

// student: display registered courses sorted by course code (selection sort)
void SystemManager::displayTimetableSortedByCourseCode(const Student &s) const {
    if (s.getTotalRegistered() == 0) { std::cout << "No courses registered yet!" << std::endl; return; }
    Course regs[10];
    int regsCount = 0;
    for (int i = 0; i < s.getTotalRegistered() && regsCount < 10; ++i) {
        int idx = searchCourseByCode(s.getRegistered(i));
        if (idx != -1) regs[regsCount++] = getCourseAt(idx);
    }
    if (regsCount == 0) { std::cout << "No valid registered courses to display." << std::endl; return; }
    selectionSortCourses(regs, regsCount, "code", true);
    std::cout << "\nYour Registered Courses (sorted by course code):\n";
    std::cout << std::left << std::setw(10) << "Code" << " | " << std::setw(30) << "Name" << " | " << std::setw(5) << "CH" << " | " << std::setw(18) << "Lecturer" << " | " << std::setw(10) << "Day" << " | " << std::setw(13) << "Time" << " | " << std::setw(8) << "Venue" << std::endl;
    for (int i = 0; i < regsCount; ++i) regs[i].display();
}

// student: display registered courses sorted by lecturer name (bubble sort)
void SystemManager::displayTimetableSortedByLecturerName(const Student &s) const {
    if (s.getTotalRegistered() == 0) { std::cout << "No courses registered yet!" << std::endl; return; }
    Course regs[10];
    int regsCount = 0;
    for (int i = 0; i < s.getTotalRegistered() && regsCount < 10; ++i) {
        int idx = searchCourseByCode(s.getRegistered(i));
        if (idx != -1) regs[regsCount++] = getCourseAt(idx);
    }
    if (regsCount == 0) { std::cout << "No valid registered courses to display." << std::endl; return; }
    bubbleSortCourses(regs, regsCount, "lecturer", true);
    std::cout << "\nYour Registered Courses (sorted by lecturer):\n";
    std::cout << std::left << std::setw(10) << "Code" << " | " << std::setw(30) << "Name" << " | " << std::setw(5) << "CH" << " | " << std::setw(18) << "Lecturer" << " | " << std::setw(10) << "Day" << " | " << std::setw(13) << "Time" << " | " << std::setw(8) << "Venue" << std::endl;
    for (int i = 0; i < regsCount; ++i) regs[i].display();
}

// student: display registered courses sorted by credit hour (insertion sort)
void SystemManager::displayTimetableSortedByCreditHour(const Student &s) const {
    if (s.getTotalRegistered() == 0) { std::cout << "No courses registered yet!" << std::endl; return; }
    Course regs[10];
    int regsCount = 0;
    for (int i = 0; i < s.getTotalRegistered() && regsCount < 10; ++i) {
        int idx = searchCourseByCode(s.getRegistered(i));
        if (idx != -1) regs[regsCount++] = getCourseAt(idx);
    }
    if (regsCount == 0) { std::cout << "No valid registered courses to display." << std::endl; return; }
    insertionSortCourses(regs, regsCount, "credit", true);
    std::cout << "\nYour Registered Courses (sorted by credit hour):\n";
    std::cout << std::left << std::setw(10) << "Code" << " | " << std::setw(30) << "Name" << " | " << std::setw(5) << "CH" << " | " << std::setw(18) << "Lecturer" << " | " << std::setw(10) << "Day" << " | " << std::setw(13) << "Time" << " | " << std::setw(8) << "Venue" << std::endl;
    for (int i = 0; i < regsCount; ++i) regs[i].display();
}

void SystemManager::addCourse() {
    Course c;
    std::cin.ignore();

    std::cout << "Enter course code: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    c.setCourseCode(tmp);

    std::cout << "Enter course name: ";
    std::getline(std::cin, tmp);
    c.setCourseName(tmp);

    std::cout << "Enter credit hour: ";
    int ch;
    std::cin >> ch;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid credit hour! Defaulting to 0.\n";
        ch = 0;
    }

    c.setCreditHour(ch);
    std::cin.ignore();

    std::cout << "Enter lecturer name: ";
    std::getline(std::cin, tmp);
    c.setLecturer(tmp);

    std::cout << "Enter day: ";
    std::getline(std::cin, tmp);
    c.setDay(tmp);

    std::cout << "Enter time: ";
    std::getline(std::cin, tmp);
    c.setTime(tmp);

    std::cout << "Enter venue: ";
    std::getline(std::cin, tmp);
    c.setVenue(tmp);

    CourseNode* newNode = new CourseNode;
    newNode->course = c;
    newNode->next = nullptr;
    
    if (head == nullptr) {
        head = newNode;
    } else {
        CourseNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    totalCourses++;

    saveCoursesToFile();  
}

void SystemManager::deleteCourse() {
    std::string code;
    std::cout << "Enter course code to delete: ";
    std::cin >> code;

    if (head == nullptr) {
        std::cout << "Course not found!\n";
        return;
    }

    if (head->course.getCourseCode() == code) {
        CourseNode* toDelete = head;
        head = head->next;
        delete toDelete;
        totalCourses--;
        std::cout << "Course deleted successfully!\n";
        saveCoursesToFile();
        return;
    }

    CourseNode* current = head;
    while (current->next != nullptr) {
        if (current->next->course.getCourseCode() == code) {
            CourseNode* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            totalCourses--;
            std::cout << "Course deleted successfully!\n";
            saveCoursesToFile();
            return;
        }
        current = current->next;
    }

    std::cout << "Course not found!\n";
}

void SystemManager::saveCoursesToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error writing to file!\n";
        return;
    }

    CourseNode* current = head;
    while (current != nullptr) {
        file << current->course.getCourseCode() << "|"
             << current->course.getCourseName() << "|"
             << current->course.getCreditHour() << "|"
             << current->course.getLecturer() << "|"
             << current->course.getDay() << "|"
             << current->course.getTime() << "|"
             << current->course.getVenue();
        
        if (current->next != nullptr)
            file << "\n";
        
        current = current->next;
    }

    file.close();
    std::cout << "Changes saved to courses.txt successfully!\n";
}


static std::string toLowerStr(const std::string &s) {
    std::string out;
    out.reserve(s.size());
    for (char ch : s) out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    return out;
}

static bool compareCoursesField(const Course &a, const Course &b, const std::string &field, bool ascending) {
    if (field == "credit") {
        if (ascending) return a.getCreditHour() < b.getCreditHour();
        else return a.getCreditHour() > b.getCreditHour();
    }

    std::string va, vb;
    if (field == "code") {
        va = toLowerStr(a.getCourseCode());
        vb = toLowerStr(b.getCourseCode());
    } else if (field == "lecturer") {
        va = toLowerStr(a.getLecturer());
        vb = toLowerStr(b.getLecturer());
    } else if (field == "name") {
        va = toLowerStr(a.getCourseName());
        vb = toLowerStr(b.getCourseName());
    } else {
        va = toLowerStr(a.getCourseCode());
        vb = toLowerStr(b.getCourseCode());
    }

    if (ascending) return va < vb;
    return va > vb;
}

void SystemManager::selectionSortCourses(Course list[], int n, const std::string &field, bool ascending) const {
    for (int i = 0; i < n - 1; ++i) {
        int sel = i;
        for (int j = i + 1; j < n; ++j) {
            if (compareCoursesField(list[j], list[sel], field, ascending)) {
                sel = j;
            }
        }
        if (sel != i) std::swap(list[i], list[sel]);
    }
}

void SystemManager::bubbleSortCourses(Course list[], int n, const std::string &field, bool ascending) const {
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (compareCoursesField(list[j + 1], list[j], field, ascending)) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void SystemManager::insertionSortCourses(Course list[], int n, const std::string &field, bool ascending) const {
    for (int i = 1; i < n; ++i) {
        Course key = list[i];
        int j = i - 1;
        while (j >= 0 && compareCoursesField(key, list[j], field, ascending)) {
            list[j + 1] = list[j];
            --j;
        }
        list[j + 1] = key;
    }
}

int SystemManager::getTotalCourses() const { return totalCourses; }

const Course &SystemManager::getCourseAt(int index) const {
    CourseNode* current = head;
    for (int i = 0; i < index; ++i) {
        if (current == nullptr) throw std::out_of_range("Index out of bounds"); // Should generally be safe with valid index
        current = current->next;
    }

    if (current == nullptr) throw std::out_of_range("Index out of bounds during access"); // Using exception or fallback if preferred, though logic expects valid index
    return current->course;
}

