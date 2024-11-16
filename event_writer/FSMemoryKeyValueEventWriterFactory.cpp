#include "FSMemoryKeyValueEventWriterFactory.h"

// Constructor initializes output file name from the configuration
FSMemoryKeyValueEventWriterFactory::FSMemoryKeyValueEventWriterFactory(const ConfigurationValues *configurationManager)
        : m_output_file(configurationManager->outputFile) {}

// Returns a new FSMemoryKeyValueEventWriter instance
EventWriter* FSMemoryKeyValueEventWriterFactory::getWriter() const {
    return new FSMemoryKeyValueEventWriter();
}
