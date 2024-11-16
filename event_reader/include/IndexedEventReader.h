//
// Created by pablo on 4/8/22.
//

#ifndef CHRONOSQL_INDEXEDEVENTREADER_H
#define CHRONOSQL_INDEXEDEVENTREADER_H

#include "DiskEventReader.h"
#include <list>
#include <utility>

class IndexedEventReader : public DiskEventReader {
public:
    explicit IndexedEventReader(int _fixedPayloadSize);

    std::list<std::pair<EID, const char *>> *
    readEventsInRange(const CID &cid, std::time_t start, std::time_t end) override;
};

#endif // CHRONOSQL_INDEXEDEVENTREADER_H
