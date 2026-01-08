#include "Student.h"
#include <iostream>

Student::Student()
    : studentID(""), studentName(""), head(nullptr), totalRegistered(0) {}

Student::~Student() {
    CourseCodeNode* current = head;
    while (current != nullptr) {
        CourseCodeNode* next = current->next;
        delete current;
        current = next;
    }
}

void Student::registerCourse(const std::string &code) {
    if (totalRegistered >= 10) {
        std::cout << "Maximum course limit reached!" << std::endl;
        return;
    }
    // Prevent duplicate registration
    if (isRegistered(code)) {
        std::cout << "Already registered for course " << code << "!" << std::endl;
        return;
    }
    
    CourseCodeNode* newNode = new CourseCodeNode;
    newNode->courseCode = code;
    newNode->next = nullptr;
    
    if (head == nullptr) {
        head = newNode;
    } else {
        CourseCodeNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    totalRegistered++;
    std::cout << "Course " << code << " registered!" << std::endl;
}

void Student::dropCourse(const std::string &code) {
    if (head == nullptr) {
        std::cout << "Course not found in your registration!" << std::endl;
        return;
    }

    if (head->courseCode == code) {
        CourseCodeNode* toDelete = head;
        head = head->next;
        delete toDelete;
        totalRegistered--;
        std::cout << "Course dropped successfully." << std::endl;
        return;
    }

    CourseCodeNode* current = head;
    while (current->next != nullptr) {
        if (current->next->courseCode == code) {
            CourseCodeNode* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            totalRegistered--;
            std::cout << "Course dropped successfully." << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Course not found in your registration!" << std::endl;
}

void Student::displayTimetable() const {
    if (totalRegistered == 0) {
        std::cout << "No courses registered yet!" << std::endl;
        return;
    }
    std::cout << "\nYour Registered Courses:\n";
    CourseCodeNode* current = head;
    while (current != nullptr) {
        std::cout << "- " << current->courseCode << std::endl;
        current = current->next;
    }
}

bool Student::isRegistered(const std::string &code) const {
    CourseCodeNode* current = head;
    while (current != nullptr) {
        if (current->courseCode == code) return true;
        current = current->next;
    }
    return false;
}

int Student::getTotalRegistered() const { return totalRegistered; }

std::string Student::getRegistered(int index) const {
    if (index < 0 || index >= totalRegistered) return std::string();
    CourseCodeNode* current = head;
    for (int i = 0; i < index; ++i) {
        if (current == nullptr) return std::string();
        current = current->next;
    }
    if (current != nullptr) return current->courseCode;
    return std::string();
}

void Student::setStudentID(const std::string &id) { studentID = id; }
void Student::setStudentName(const std::string &name) { studentName = name; }
std::string Student::getStudentID() const { return studentID; }
std::string Student::getStudentName() const { return studentName; }
