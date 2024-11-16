//
// Created by pablo on 4/8/22.
//

#ifndef CHRONOSQL_INDEXEDEVENTREADERFACTORY_H
#define CHRONOSQL_INDEXEDEVENTREADERFACTORY_H

#include <memory>
#include "ConfigurationValues.h"
#include "EventReader.h"
#include "IndexedEventReader.h"

class IndexedEventReaderFactory {
public:
    explicit IndexedEventReaderFactory(const ConfigurationValues* config);

    [[nodiscard]] std::unique_ptr<EventReader> getReader() const;

private:
    int fixedPayloadSize;
};

#endif // CHRONOSQL_INDEXEDEVENTREADERFACTORY_H
