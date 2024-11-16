//
// Created by pablo on 27/05/2022.
//

#ifndef CHRONOSQL_INDEXEDKEYVALUEEVENTWRITERFACTORY_H
#define CHRONOSQL_INDEXEDKEYVALUEEVENTWRITERFACTORY_H

#include <string>
#include "ConfigurationValues.h"
#include "EventWriter.h"
#include "IndexedKeyValueEventWriter.h"

class IndexedKeyValueEventWriterFactory {

public:
    explicit IndexedKeyValueEventWriterFactory(const ConfigurationValues *configurationManager);

    [[nodiscard]] EventWriter *getWriter() const;

private:
    int payloadSize;
    int indexIntervalBytes;
};

#endif // CHRONOSQL_INDEXEDKEYVALUEEVENTWRITERFACTORY_H
