//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_FSEVENTREADERFACTORY_H
#define CHRONOSQL_FSEVENTREADERFACTORY_H

#include <memory>
#include "EventReader.h"
#include "FSEventReader.h"
#include "Constants.h"
#include "ConfigurationValues.h"

using namespace Constants;

class FSEventReaderFactory {
public:
    explicit FSEventReaderFactory(const ConfigurationValues* config);

    [[nodiscard]] std::unique_ptr<EventReader> getReader() const;

private:
    int fixedPayloadSize;
};

#endif // CHRONOSQL_FSEVENTREADERFACTORY_H
