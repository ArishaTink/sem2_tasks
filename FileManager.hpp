#pragma once

#include <string>
#include "Group.hpp"

class FileManager {
public:
    static void saveToFile(const Group& group, const std::string& filename);
    static Group loadFromFile(const std::string& filename);
};