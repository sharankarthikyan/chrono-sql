#include "FSEventReaderFactory.h"

FSEventReaderFactory::FSEventReaderFactory(const ConfigurationValues* config)
    : fixedPayloadSize(config->fixedPayloadSize) {}

std::unique_ptr<EventReader> FSEventReaderFactory::getReader() const {
    return std::make_unique<FSEventReader>(fixedPayloadSize);
}
