#include "IndexedKeyValueEventWriterFactory.h"

// Constructor initializes payload size and index interval from configuration
IndexedKeyValueEventWriterFactory::IndexedKeyValueEventWriterFactory(const ConfigurationValues *configurationManager)
        : payloadSize(configurationManager->payloadSize),
          indexIntervalBytes(configurationManager->indexIntervalBytes) {}

// Creates and returns a new IndexedKeyValueEventWriter instance
EventWriter* IndexedKeyValueEventWriterFactory::getWriter() const {
    return new IndexedKeyValueEventWriter(this->payloadSize, this->indexIntervalBytes);
}
