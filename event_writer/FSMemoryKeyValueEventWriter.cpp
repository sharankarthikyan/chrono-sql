#include "FSMemoryKeyValueEventWriter.h"

// Constructor initializes the memory event storage
FSMemoryKeyValueEventWriter::FSMemoryKeyValueEventWriter() {
    MemoryEventStorage::initialize();
}

// Writes a single event to memory storage
int FSMemoryKeyValueEventWriter::write(const CID &cid, Event *event) {
    auto *kvEvent = dynamic_cast<KeyValueEvent *>(event);
    if (kvEvent != nullptr) {
        MemoryEventStorage::addEvent(cid, kvEvent);
        return 0;
    }

    return -1;
}

// Writes a list of events to memory storage
int FSMemoryKeyValueEventWriter::write(const CID &cid, std::list<Event *> events) {
    for (auto const i : events) {
        auto *kvEvent = dynamic_cast<KeyValueEvent *>(i);
        if (kvEvent != nullptr) {
            MemoryEventStorage::addEvent(cid, kvEvent);
        }
    }

    return 0;
}
