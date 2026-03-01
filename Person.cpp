#include "Person.hpp"
#include <iostream>

void Person::print() const {
    std::cout << "Name: " << name << std::endl;
}