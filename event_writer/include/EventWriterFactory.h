//
// Created by pablo on 16/05/2022.
//

#ifndef CHRONOSQL_EVENTWRITERFACTORY_H
#define CHRONOSQL_EVENTWRITERFACTORY_H

#include "FSMemoryKeyValueEventWriterFactory.h"
#include "FSKeyValueEventWriterFactory.h"
#include "IndexedKeyValueEventWriterFactory.h"
#include "ConfigurationValues.h"  // Assuming this file defines ConfigurationValues and EventType

class EventWriterFactory {
public:
    EventWriter *getWriter(const ConfigurationValues *config);
};

#endif // CHRONOSQL_EVENTWRITERFACTORY_H
