#include "ChronoLog.h"

// Constructor that initializes EventWriter and EventReader
ChronoLog::ChronoLog(ConfigurationValues *config) : configuration(config) {
    auto *writerFactory = new EventWriterFactory();
    auto *readerFactory = new EventReaderFactory();
    eventWriter = writerFactory->getWriter(config);
    eventReader = readerFactory->getReader(config).release(); 
}

// Method to record an event
EID ChronoLog::record(const CID &cid, const char *data) {
    EID id = std::time(nullptr);
    auto *event = new KeyValueEvent(id, data);
    eventWriter->write(cid, event);
    return id;
}

// Method to playback the last event for a given CID
const char *ChronoLog::playback(const CID &cid) {
    return eventReader->readLastEvent(cid);
}

// Method to replay events in a specified range for a given CID
std::list<std::pair<EID, const char *>> *ChronoLog::replay(const CID &cid, EID startEID, EID endEID) {
    return eventReader->readEventsInRange(cid, startEID, endEID);
}
