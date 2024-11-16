#include "MemEventReaderFactory.h"

MemEventReaderFactory::MemEventReaderFactory(const ConfigurationValues* config) {
    reader = std::make_unique<MemEventReader>();
}

std::unique_ptr<EventReader> MemEventReaderFactory::getReader() const {
    // Clone or create a new instance of MemEventReader if each call should return a new reader
    return std::make_unique<MemEventReader>(*reader);
}
