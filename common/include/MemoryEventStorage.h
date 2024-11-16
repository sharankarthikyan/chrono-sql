//
// Created by pablo on 31/05/2022.
//

#ifndef CHRONOSQL_MEMORYEVENTSTORAGE_H
#define CHRONOSQL_MEMORYEVENTSTORAGE_H

#include <list>
#include <map>
#include <iostream>
#include "Event.h"
#include "ChronicleNotFoundException.h"
#include "typedefs.h" 

class MemoryEventStorage {
public:
    // Initializes the storage
    static void initialize();

    // Gets events for a given CID
    static std::list<Event *> *getEvents(const CID &cid);

    // Adds an event to a given CID
    static void addEvent(const CID &cid, Event *event);

    // Dumps the contents of the storage
    static void dumpContents();

private:
    // Map to hold events associated with each CID
    static std::map<CID, std::list<Event *> *> events;
};

#endif // CHRONOSQL_MEMORYEVENTSTORAGE_H
