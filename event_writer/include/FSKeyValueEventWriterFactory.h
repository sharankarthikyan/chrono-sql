//
// Created by pablo on 16/05/2022.
//

#ifndef CHRONOSQL_FSKEYVALUEEVENTWRITERFACTORY_H
#define CHRONOSQL_FSKEYVALUEEVENTWRITERFACTORY_H

#include "EventWriterFactory.h"
#include "FSKeyValueEventWriter.h"
#include "ConfigurationManager.h"

class FSKeyValueEventWriterFactory {
public:
    explicit FSKeyValueEventWriterFactory(const ConfigurationValues *configurationManager);

    [[nodiscard]] EventWriter *getWriter() const;

private:
    std::string m_output_file;
    int payloadSize;
};

#endif // CHRONOSQL_FSKEYVALUEEVENTWRITERFACTORY_H
