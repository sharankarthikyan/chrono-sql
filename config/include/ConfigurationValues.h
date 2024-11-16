//
// Created by pablo on 21/05/2022.
//

#ifndef CHRONOSQL_CONFIGURATIONVALUES_H
#define CHRONOSQL_CONFIGURATIONVALUES_H

#include <string>
#include "Enumerations.h"

using namespace Enumerations;

class ConfigurationValues {

public:
    ConfigurationValues() noexcept; 

    // Common configuration
    int nEvents = 0;
    EventType eventType;
    std::string outputFile;

    // Key-value configuration
    int payloadSize = 0;
    int payloadVariation = 0;
    int fixedPayloadSize = 0;
    long lowerTimestamp = 1628202739;
    long higherTimestamp = 1659738749;

    // Indexing configuration
    int indexIntervalBytes = 4096;

    // Testing configuration
    bool hideOutput = false;
    int nExecutions = 3;
    std::string sqlFilePath;
};

#endif // CHRONOSQL_CONFIGURATIONVALUES_H
