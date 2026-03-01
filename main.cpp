#include "Student.hpp"
#include "Group.hpp"
#include "FileManager.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    try {
        Student* s1 = new Student("Alice", "RB001");
        s1->addGrade(5);
        s1->addGrade(4);

        Student* s2 = new Student("Bob", "RB002");
        s2->addGrade(3);
        s2->addGrade(4);

        Group group("Group1");
        group.addStudent(s1);
        group.addStudent(s2);

        std::cout << "Original group:" << std::endl;
        group.printAll();

        group.sortByAverage();
        std::cout << "After sorting by average:" << std::endl;
        group.printAll();

        auto filtered = group.filterByThreshold(4.0);
        std::cout << "Filtered students with average >= 4.0:" << std::endl;
        for (auto* s : filtered) {
            s->print();
            std::cout << "--------" << std::endl;
        }

        FileManager::saveToFile(group, "group.bin");

        Group loaded = FileManager::loadFromFile("group.bin");
        std::cout << "Loaded group:" << std::endl;
        loaded.printAll();

        delete s1;
        delete s2;

        for (auto* s : loaded.getStudents()) {
            delete s;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}