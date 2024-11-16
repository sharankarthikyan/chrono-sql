//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_FSEVENTREADER_H
#define CHRONOSQL_FSEVENTREADER_H

#include "EventReader.h"
#include "DiskEventReader.h"
#include "ConfigurationValues.h"
#include <list>
#include <utility>

class FSEventReader : public DiskEventReader {
public:
    explicit FSEventReader(int fixedPayloadSize_);

    std::list<std::pair<EID, const char *>> *
    readEventsInRange(const CID &cid, std::time_t start, std::time_t end) override;
};

#endif // CHRONOSQL_FSEVENTREADER_H
