#include "Student.hpp"
#include <iostream>
#include <stdexcept>

Student::Student(const std::string& n, const std::string& rbNum) : Person(n), recordBook(rbNum) {
    if (n.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
}

void Student::addGrade(int grade) {
    recordBook.addGrade(grade);
}

double Student::calculateAverage() const {
    return recordBook.calculateAverage();
}

void Student::print() const {
    Person::print();
    std::cout << "Record Book: " << recordBook.getNumber() << std::endl;
    recordBook.printGrades();
    std::cout << "Average: " << calculateAverage() << std::endl;
}