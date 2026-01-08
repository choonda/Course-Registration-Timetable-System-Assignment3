#include "Course.h"
#include <iostream>
#include <iomanip>

Course::Course()
        : courseCode(""), courseName(""), creditHour(0),
            lecturer(""), day(""), time(""), venue("") {}

void Course::display() const {
    std::cout << std::left
              << std::setw(10) << courseCode << " | "
              << std::setw(30) << courseName << " | "
              << std::setw(5)  << creditHour   << " | "
              << std::setw(18) << lecturer     << " | "
              << std::setw(10) << day          << " | "
              << std::setw(13) << time         << " | "
              << std::setw(8)  << venue        << std::endl;
}

std::string Course::getCourseCode() const {
    return courseCode;
}

std::string Course::getCourseName() const { return courseName; }
int Course::getCreditHour() const { return creditHour; }
std::string Course::getLecturer() const { return lecturer; }
std::string Course::getDay() const { return day; }
std::string Course::getTime() const { return time; }
std::string Course::getVenue() const { return venue; }

void Course::setCourseCode(const std::string &c) { courseCode = c; }
void Course::setCourseName(const std::string &n) { courseName = n; }
void Course::setCreditHour(int ch) { creditHour = ch; }
void Course::setLecturer(const std::string &l) { lecturer = l; }
void Course::setDay(const std::string &d) { day = d; }
void Course::setTime(const std::string &t) { time = t; }
void Course::setVenue(const std::string &v) { venue = v; }
