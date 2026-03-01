#pragma once

#include <vector>
#include <string>
#include "Student.hpp"

class Group {
private:
    std::string name;
    std::vector<Student*> students;

public:
    Group(const std::string& n) : name(n) {}

    void addStudent(Student* s);
    void removeStudent(const std::string& studentName);
    void printAll() const;
    double calculateGroupAverage() const;
    void sortByAverage();
    std::vector<Student*> filterByThreshold(double threshold) const;

    const std::string& getName() const { return name; }
    const std::vector<Student*>& getStudents() const { return students; }
};