#pragma once

#include "Person.hpp"
#include <string>

class Teacher : public Person {
private:
    std::string discipline;

public:
    Teacher(const std::string& n, const std::string& d) : Person(n), discipline(d) {}

    void print() const override;
};