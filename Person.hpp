#pragma once

#include <string>

class Person {
protected:
    std::string name;

public:
    Person(const std::string& n = "") : name(n) {}

    virtual void print() const;

    virtual ~Person() = default;

    const std::string& getName() const { return name; }
};