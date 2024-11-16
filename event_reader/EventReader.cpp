#include "EventReader.h"
#include <iostream>

std::ifstream EventReader::openReadFile(const std::string &filename) {
    std::ifstream input_file(filename, std::ios::in | std::ios::ate | std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return input_file;
}
