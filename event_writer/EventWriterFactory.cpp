#include "EventWriterFactory.h"

// Implementation of getWriter function
EventWriter* EventWriterFactory::getWriter(const ConfigurationValues *config) {
    if (config->eventType == EventType::MEMORY_KEY_VALUE) {
        auto *memFactory = new FSMemoryKeyValueEventWriterFactory(config);
        return memFactory->getWriter();
    } else if (config->eventType == EventType::FIXED_KEY_VALUE) {
        auto *fixedFactory = new FSKeyValueEventWriterFactory(config);
        return fixedFactory->getWriter();
    } else if (config->eventType == EventType::INDEXED_KEY_VALUE) {
        auto *indexFactory = new IndexedKeyValueEventWriterFactory(config);
        return indexFactory->getWriter();
    }

    return nullptr;
}
