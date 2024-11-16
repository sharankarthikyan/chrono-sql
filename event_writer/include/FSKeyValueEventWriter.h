//
// Created by pablo on 16/05/2022.
//

#ifndef CHRONOSQL_FSKEYVALUEEVENTWRITER_H
#define CHRONOSQL_FSKEYVALUEEVENTWRITER_H

#include <iostream>
#include <fstream>
#include <list>
#include "EventWriter.h"
#include "Constants.h"
#include "KeyValueEvent.h"
#include "EventWriterUtils.h"

using namespace Constants;

class FSKeyValueEventWriter : public EventWriter {

public:
    explicit FSKeyValueEventWriter(int _fixedPayloadSize);

    int write(const CID &cid, Event *event) override;

    int write(const CID &cid, std::list<Event *> events) override;

private:
    const int fixedPayloadSize;
    EventWriterUtils *writerUtils;

    static KeyValueEvent *toKeyValue(Event *event);

    void writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, const char *payload);
};

#endif // CHRONOSQL_FSKEYVALUEEVENTWRITER_H
