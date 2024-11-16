//
// Created by pablo on 31/05/2022.
//

#ifndef CHRONOSQL_MEMEVENTREADERFACTORY_H
#define CHRONOSQL_MEMEVENTREADERFACTORY_H

#include <memory>
#include "Constants.h"
#include "ConfigurationValues.h"
#include "EventReader.h"
#include "MemEventReader.h"

using namespace Constants;

class MemEventReaderFactory {
public:
    explicit MemEventReaderFactory(const ConfigurationValues* config);

    [[nodiscard]] std::unique_ptr<EventReader> getReader() const;

private:
    std::unique_ptr<MemEventReader> reader;
};

#endif // CHRONOSQL_MEMEVENTREADERFACTORY_H
