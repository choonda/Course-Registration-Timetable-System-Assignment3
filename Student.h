#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    struct CourseCodeNode {
        std::string courseCode;
        CourseCodeNode* next;
    };

    std::string studentID;
    std::string studentName;
    CourseCodeNode* head;
    int totalRegistered;

public:
    Student();
    ~Student();

    void registerCourse(const std::string &code);
    void dropCourse(const std::string &code);
    void displayTimetable() const;
    bool isRegistered(const std::string &code) const;
    int getTotalRegistered() const;
    std::string getRegistered(int index) const;
    // optional accessors for student fields
    void setStudentID(const std::string &id);
    void setStudentName(const std::string &name);
    std::string getStudentID() const;
    std::string getStudentName() const;
};

#endif // STUDENT_H
