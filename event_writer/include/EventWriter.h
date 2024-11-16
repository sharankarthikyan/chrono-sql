//
// Created by pablo on 16/05/2022.
//

#ifndef CHRONOSQL_EVENTWRITER_H
#define CHRONOSQL_EVENTWRITER_H

#include <string>
#include <fstream>
#include <list>
#include "Event.h"
#include "typedefs.h"

class EventWriter {

public:
    // Pure virtual functions for derived classes to implement
    virtual int write(const CID &cid, Event *event) = 0;

    virtual int write(const CID &cid, std::list<Event *> events) = 0;

    // Static function to open a file for writing
    static std::ofstream openWriteFile(const std::string &filename);
};

#endif // CHRONOSQL_EVENTWRITER_H
