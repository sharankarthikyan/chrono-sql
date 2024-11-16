#include "FSKeyValueEventWriterFactory.h"

// Constructor initializes the output file and payload size from the configuration
FSKeyValueEventWriterFactory::FSKeyValueEventWriterFactory(const ConfigurationValues *configurationManager)
        : m_output_file(configurationManager->outputFile),
          payloadSize(configurationManager->payloadSize) {}

// Returns a new FSKeyValueEventWriter instance configured with the payload size
EventWriter* FSKeyValueEventWriterFactory::getWriter() const {
    return new FSKeyValueEventWriter(payloadSize);
}
