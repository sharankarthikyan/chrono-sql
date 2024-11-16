//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_EVENTREADERFACTORY_H
#define CHRONOSQL_EVENTREADERFACTORY_H

#include <memory>
#include "EventReader.h"
#include "ConfigurationValues.h"
#include "FSEventReaderFactory.h"
#include "MemEventReaderFactory.h"
#include "IndexedEventReaderFactory.h"

class EventReaderFactory {
public:
    // Function to get an EventReader based on configuration
    std::unique_ptr<EventReader> getReader(const ConfigurationValues* config);
};

#endif // CHRONOSQL_EVENTREADERFACTORY_H
