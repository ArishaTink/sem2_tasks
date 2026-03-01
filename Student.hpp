#pragma once

#include "Person.hpp"
#include "RecordBook.hpp"
#include <string>

class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student(const std::string& n, const std::string& rbNum);

    void addGrade(int grade);
    double calculateAverage() const;
    void print() const override;

    const RecordBook& getRecordBook() const { return recordBook; }
};