//
// Created by pablo on 30/05/2022.
//

#ifndef CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITERFACTORY_H
#define CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITERFACTORY_H

#include "ConfigurationValues.h"
#include "EventWriter.h"
#include "FSMemoryKeyValueEventWriter.h"

class FSMemoryKeyValueEventWriterFactory {

public:
    explicit FSMemoryKeyValueEventWriterFactory(const ConfigurationValues *configurationManager);

    [[nodiscard]] EventWriter *getWriter() const;

private:
    std::string m_output_file;
};

#endif // CHRONOSQL_FSMEMORYKEYVALUEEVENTWRITERFACTORY_H
