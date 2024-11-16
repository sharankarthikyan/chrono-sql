//
// Created by pablo on 31/05/2022.
//

#ifndef CHRONOSQL_MEMEVENTREADER_H
#define CHRONOSQL_MEMEVENTREADER_H

#include <list>
#include "EventReader.h"
#include "Event.h"
#include "KeyValueEvent.h"

class MemEventReader : public EventReader {
public:
    explicit MemEventReader();

    const char *readLastEvent(const CID &cid) override;

    std::list<std::pair<EID, const char *>> *
    readEventsInRange(const CID &cid, std::time_t start, std::time_t end) override;
};

#endif // CHRONOSQL_MEMEVENTREADER_H
