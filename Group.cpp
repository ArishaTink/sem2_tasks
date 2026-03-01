#include "Group.hpp"
#include <iostream>
#include <algorithm>

void Group::addStudent(Student* s) {
    students.push_back(s);
}

void Group::removeStudent(const std::string& studentName) {
    students.erase(std::remove_if(students.begin(), students.end(),
        [&studentName](const Student* s) { return s->getName() == studentName; }),
        students.end());
}

void Group::printAll() const {
    std::cout << "Group: " << name << std::endl;
    for (const auto* s : students) {
        s->print();
        std::cout << "--------" << std::endl;
    }
}

double Group::calculateGroupAverage() const {
    if (students.empty()) return 0.0;
    double sum = 0.0;
    for (const auto* s : students) {
        sum += s->calculateAverage();
    }
    return sum / students.size();
}

void Group::sortByAverage() {
    std::sort(students.begin(), students.end(),
        [](const Student* a, const Student* b) {
            return a->calculateAverage() > b->calculateAverage();
        });
}

std::vector<Student*> Group::filterByThreshold(double threshold) const {
    std::vector<Student*> filtered;
    for (const auto* s : students) {
        if (s->calculateAverage() >= threshold) {
            filtered.push_back(const_cast<Student*>(s));
        }
    }
    return filtered;
}