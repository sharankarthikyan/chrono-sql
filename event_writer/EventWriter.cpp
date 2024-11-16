#include "EventWriter.h"

// Opens a file for writing, with append mode
std::ofstream EventWriter::openWriteFile(const std::string &filename) {
    std::ofstream output_file;
    output_file.open(filename, std::ios::out | std::ios::app);
    return output_file;
}
