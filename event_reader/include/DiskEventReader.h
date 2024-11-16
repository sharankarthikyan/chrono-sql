//
// Created by pablo on 4/8/22.
//

#ifndef CHRONOSQL_DISKEVENTREADER_H
#define CHRONOSQL_DISKEVENTREADER_H

#include <fstream>
#include <list>
#include <string>
#include "EventReader.h"

class DiskEventReader : public EventReader {
public:
    explicit DiskEventReader(int _fixedPayloadSize);

    const char *readLastEvent(const CID &cid) override;

    std::list<std::pair<EID, const char *>> *
    readEventsInRange(const std::string &filename, long pos, std::time_t start, std::time_t end);

protected:
    int fixedPayloadSize;

private:
    std::ifstream openReadFile(const std::string &filename) const;
};

#endif //CHRONOSQL_DISKEVENTREADER_H
