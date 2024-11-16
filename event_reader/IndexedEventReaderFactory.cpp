#include "IndexedEventReaderFactory.h"

IndexedEventReaderFactory::IndexedEventReaderFactory(const ConfigurationValues* config) {
    fixedPayloadSize = config->fixedPayloadSize;
}

std::unique_ptr<EventReader> IndexedEventReaderFactory::getReader() const {
    return std::make_unique<IndexedEventReader>(fixedPayloadSize);
}
