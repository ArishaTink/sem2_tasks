#include "Teacher.hpp"
#include <iostream>

void Teacher::print() const {
    Person::print();
    std::cout << "Discipline: " << discipline << std::endl;
}