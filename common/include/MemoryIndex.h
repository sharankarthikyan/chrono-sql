//
// Created by pablo on 4/8/22.
//

#ifndef CHRONOSQL_MEMORYINDEX_H
#define CHRONOSQL_MEMORYINDEX_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "typedefs.h"

class MemoryIndex {
public:
    // Adds an entry to the index
    static void addEntry(const CID &cid, EID eid, long longValue);

    // Gets the closest value for a given CID and EID
    static long getClosestValue(const CID &cid, EID eid);

    // Generates the index from a file associated with the given CID
    static void generate(const std::string &cid);

private:
    // Static member to hold the index data
    static std::map<CID, std::map<EID, long>> index;
};

#endif // CHRONOSQL_MEMORYINDEX_H
