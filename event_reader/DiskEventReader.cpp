#include <iostream>
#include "DiskEventReader.h"
#include "Constants.h"


DiskEventReader::DiskEventReader(int _fixedPayloadSize) : fixedPayloadSize(_fixedPayloadSize) {}

const char *DiskEventReader::readLastEvent(const CID &cid) {
    std::ifstream file = openReadFile(cid + Constants::LOG_EXTENSION);
    if (!file.is_open()) {
        return nullptr;
    }

    file.seekg(0, std::ios::end);
    int fileSize = (int) file.tellg();

    if (fileSize > fixedPayloadSize) {
        char *data = new char[fixedPayloadSize + 1];
        file.seekg(fileSize - fixedPayloadSize - 1);
        file.get(data, fixedPayloadSize + 1);
        return data;
    }

    return nullptr;
}

std::list<std::pair<EID, const char *>> *
DiskEventReader::readEventsInRange(const std::string &filename, long pos, std::time_t start, std::time_t end) {
    std::ifstream file = openReadFile(filename);
    if (!file.is_open()) {
        return nullptr;
    }

    int readSize = fixedPayloadSize + 10 + 1 + 1;
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    auto *events = new std::list<std::pair<EID, const char *>>;

    while (pos + readSize <= fileSize) {
        char *id = new char[10];
        char *data = new char[fixedPayloadSize + 1];

        file.seekg(pos);
        file.get(id, 11);
        auto eid = (std::time_t) strtol(id, nullptr, 10);

        if ((start == VOID_TIMESTAMP || eid >= start) && (end == VOID_TIMESTAMP || eid <= end)) {
            file.seekg(pos + 10 + 1);
            file.get(data, fixedPayloadSize + 1);
            events->emplace_back(eid, data);
        }

        if (end != VOID_TIMESTAMP && eid > end) {
            delete[] id;
            delete[] data;
            break;
        }

        pos += readSize;
        delete[] id;
    }

    return events;
}

std::ifstream DiskEventReader::openReadFile(const std::string &filename) const {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return file;
}
