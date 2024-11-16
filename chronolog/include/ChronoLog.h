//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_CHRONOLOG_H
#define CHRONOSQL_CHRONOLOG_H

#include <string>
#include <list>
#include "ConfigurationManager.h"
#include "EventWriter.h"
#include "EventWriterFactory.h"
#include "typedefs.h"
#include "EventReader.h"
#include "FSEventReader.h"
#include "EventReaderFactory.h"

class ChronoLog {
public:
    explicit ChronoLog(ConfigurationValues *config);
    
    // Method to record an event
    EID record(const CID &cid, const char *data);

    // Method to playback the last event
    const char *playback(const CID &cid);

    // Method to replay a range of events
    std::list<std::pair<EID, const char *>> *replay(const CID &cid, EID startEID, EID endEID);

private:
    ConfigurationValues *configuration;
    EventWriter *eventWriter;
    EventReader *eventReader;
};

#endif // CHRONOSQL_CHRONOLOG_H
