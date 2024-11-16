//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_EVENTREADER_H
#define CHRONOSQL_EVENTREADER_H

#include <fstream>
#include <string>
#include <list>
#include <utility>
#include "typedefs.h" // Assuming typedefs.h contains definitions for EID and CID

class EventReader {
public:
    virtual ~EventReader() = default;

    // Pure virtual functions to be implemented by derived classes
    virtual const char *readLastEvent(const CID &cid) = 0;

    virtual std::list<std::pair<EID, const char *>> *
    readEventsInRange(const CID &cid, std::time_t start, std::time_t end) = 0;

protected:
    static std::ifstream openReadFile(const std::string &filename);
};

#endif // CHRONOSQL_EVENTREADER_H
