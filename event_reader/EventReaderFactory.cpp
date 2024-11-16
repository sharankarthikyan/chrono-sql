#include "EventReaderFactory.h"

std::unique_ptr<EventReader> EventReaderFactory::getReader(const ConfigurationValues* config) {
    if (config->eventType == EventType::FIXED_KEY_VALUE) {
        auto factory = std::make_unique<FSEventReaderFactory>(config);
        return std::unique_ptr<EventReader>(factory->getReader());
    } else if (config->eventType == EventType::MEMORY_KEY_VALUE) {
        auto factory = std::make_unique<MemEventReaderFactory>(config);
        return std::unique_ptr<EventReader>(factory->getReader());
    } else if (config->eventType == EventType::INDEXED_KEY_VALUE) {
        auto factory = std::make_unique<IndexedEventReaderFactory>(config);
        return std::unique_ptr<EventReader>(factory->getReader());
    } else {
        return nullptr;
    }
}
