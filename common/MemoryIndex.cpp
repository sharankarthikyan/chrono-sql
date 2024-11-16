#include "MemoryIndex.h"
#include "Constants.h"

// Initialize the static member
std::map<CID, std::map<EID, long>> MemoryIndex::index;

void MemoryIndex::addEntry(const CID &cid, EID eid, long longValue) {
    index[cid][eid] = longValue;
}

long MemoryIndex::getClosestValue(const CID &cid, EID eid) {
    return index[cid].lower_bound(eid)->second;
}

void MemoryIndex::generate(const std::string &cid) {
    int pos = 0;
    auto cidFile = cid;

    std::ifstream file(cidFile.append(Constants::INDEX_EXTENSION).c_str(), std::ifstream::binary | std::ios::ate);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    while (pos <= fileSize) {
        char id[10];
        std::string offsetChar;

        file.seekg(pos);
        file.get(id, 11);
        auto eid = static_cast<std::time_t>(strtol(id, nullptr, 10));
        file.seekg(pos + 11);
        pos += 11;

        std::getline(file, offsetChar, ';');
        pos += offsetChar.length() + 1;
        if (!offsetChar.empty() && pos <= fileSize) {
            addEntry(cid, eid, std::stoi(offsetChar));
        }
    }

    std::cout << "Loaded index " << cid << ", index size: " << index[cid].size() << std::endl;
}
