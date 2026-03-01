#include "FileManager.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

static void writeString(std::ofstream& out, const std::string& str) {
    size_t len = str.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(str.data(), len);
}

static std::string readString(std::ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!in) throw std::runtime_error("File format error");
    std::string str(len, '\0');
    in.read(&str[0], len);
    if (!in) throw std::runtime_error("File format error");
    return str;
}

void FileManager::saveToFile(const Group& group, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    writeString(out, group.getName());
    size_t num_students = group.getStudents().size();
    out.write(reinterpret_cast<const char*>(&num_students), sizeof(num_students));

    for (const auto* s : group.getStudents()) {
        writeString(out, s->getName());
        writeString(out, s->getRecordBook().getNumber());
        const auto& grades = s->getRecordBook().getGrades();
        size_t num_grades = grades.size();
        out.write(reinterpret_cast<const char*>(&num_grades), sizeof(num_grades));
        out.write(reinterpret_cast<const char*>(grades.data()), sizeof(int) * num_grades);
    }

    out.close();
}

Group FileManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error opening file for reading." << std::endl;
        throw std::runtime_error("File open error");
    }

    std::string group_name = readString(in);
    Group group(group_name);

    size_t num_students;
    in.read(reinterpret_cast<char*>(&num_students), sizeof(num_students));
    if (!in) throw std::runtime_error("File format error");

    for (size_t i = 0; i < num_students; ++i) {
        std::string student_name = readString(in);
        std::string rb_number = readString(in);
        size_t num_grades;
        in.read(reinterpret_cast<char*>(&num_grades), sizeof(num_grades));
        if (!in) throw std::runtime_error("File format error");

        std::vector<int> grades(num_grades);
        in.read(reinterpret_cast<char*>(grades.data()), sizeof(int) * num_grades);
        if (!in) throw std::runtime_error("File format error");

        Student* s = new Student(student_name, rb_number);
        for (int g : grades) {
            s->addGrade(g);
        }
        group.addStudent(s);
    }

    in.close();
    return group;
}