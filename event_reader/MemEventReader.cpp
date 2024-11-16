#include "MemEventReader.h"
#include "MemoryEventStorage.h"  // Assuming this header contains MemoryEventStorage class
#include "Constants.h"            // Assuming this contains VOID_TIMESTAMP and any other constants

MemEventReader::MemEventReader() = default;

const char *MemEventReader::readLastEvent(const CID &cid) {
    auto events = MemoryEventStorage::getEvents(cid);
    if (events && !events->empty()) {
        return dynamic_cast<KeyValueEvent *>(events->back())->getPayload();
    }
    return nullptr;
}

std::list<std::pair<EID, const char *>> *
MemEventReader::readEventsInRange(const CID &cid, std::time_t start, std::time_t end) {
    auto *eventsInRange = new std::list<std::pair<EID, const char *>>;
    auto *events = MemoryEventStorage::getEvents(cid);

    if (!events) {
        return nullptr;
    }

    for (auto event : *events) {
        auto *kvEvent = dynamic_cast<KeyValueEvent *>(event);
        if ((start == VOID_TIMESTAMP || kvEvent->getTimestamp() >= start) &&
            (end == VOID_TIMESTAMP || kvEvent->getTimestamp() <= end)) {
            eventsInRange->emplace_back(kvEvent->getTimestamp(), kvEvent->getPayload());
        }

        if (end != VOID_TIMESTAMP && kvEvent->getTimestamp() > end) {
            break;
        }
    }

    return eventsInRange;
}
