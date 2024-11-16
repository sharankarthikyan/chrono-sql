//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITER_H
#define CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITER_H

#include <list>
#include "Event.h"
#include "Constants.h"
#include "EventWriter.h"
#include "KeyValueEvent.h"
#include "MemoryEventStorage.h"

using namespace Constants;

class FSMemoryKeyValueEventWriter : public EventWriter {

public:
    explicit FSMemoryKeyValueEventWriter();

    int write(const CID &cid, Event *event) override;

    int write(const CID &cid, std::list<Event *> events) override;
};

#endif // CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITER_H
