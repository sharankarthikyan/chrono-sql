#include "MemoryEventStorage.h"
#include "KeyValueEvent.h"

// Initialize the static member
std::map<CID, std::list<Event *> *> MemoryEventStorage::events;

void MemoryEventStorage::initialize() {
    // Initialization logic if needed
}

std::list<Event *> *MemoryEventStorage::getEvents(const CID &cid) {
    auto pos = events.find(cid);
    if (pos == events.end()) {
        throw ChronicleNotFoundException(); // Not found
    } else {
        return pos->second;
    }
}

void MemoryEventStorage::addEvent(const CID &cid, Event *event) {
    auto pos = events.find(cid);
    if (pos == events.end()) {
        events.insert({cid, new std::list<Event *>});
    }

    events.at(cid)->push_back(event);
}

void MemoryEventStorage::dumpContents() {
    std::cout << std::endl << "***** Dumping contents of the in-memory event storage... *****" << std::endl;
    for (const auto &chronicle : events) {
        std::cout << "Chronicle " << chronicle.first << std::endl;
        for (auto event : *chronicle.second) {
            if (auto *kvEvent = dynamic_cast<KeyValueEvent *>(event)) {
                std::cout << kvEvent->getTimestamp() << ", " << kvEvent->getPayload() << std::endl;
            }
        }
    }
    std::cout << "***** Contents successfully dumped *****" << std::endl << std::endl;
}
