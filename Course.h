#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int creditHour;
    std::string lecturer;
    std::string day;
    std::string time;
    std::string venue;

public:
    Course();
    void display() const;

    std::string getCourseCode() const;
    std::string getCourseName() const;
    int getCreditHour() const;
    std::string getLecturer() const;
    std::string getDay() const;
    std::string getTime() const;
    std::string getVenue() const;

    void setCourseCode(const std::string &c);
    void setCourseName(const std::string &n);
    void setCreditHour(int ch);
    void setLecturer(const std::string &l);
    void setDay(const std::string &d);
    void setTime(const std::string &t);
    void setVenue(const std::string &v);
};

#endif
