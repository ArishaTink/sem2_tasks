#include "RecordBook.hpp"
#include <iostream>
#include <numeric>

void RecordBook::addGrade(int grade) {
    grades.push_back(grade);
}

double RecordBook::calculateAverage() const {
    if (grades.empty()) return 0.0;
    return std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
}

void RecordBook::printGrades() const {
    std::cout << "Grades: ";
    for (int g : grades) {
        std::cout << g << " ";
    }
    std::cout << std::endl;
}