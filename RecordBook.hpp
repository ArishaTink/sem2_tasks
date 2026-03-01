#pragma once

#include <vector>
#include <string>

class RecordBook {
private:
    std::string number;
    std::vector<int> grades;

public:
    RecordBook(const std::string& num) : number(num) {}

    void addGrade(int grade);
    double calculateAverage() const;
    void printGrades() const;

    const std::string& getNumber() const { return number; }
    const std::vector<int>& getGrades() const { return grades; }
};