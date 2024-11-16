//
// Created by pablo on 21/05/2022.
//

#ifndef CHRONOSQL_CONFIGURATIONMANAGER_H
#define CHRONOSQL_CONFIGURATIONMANAGER_H

#include <string>
#include "document.h"
#include "Enumerations.h"
#include "ConfigConstants.h"
#include "ConfigurationValues.h"

using namespace rapidjson;
using namespace Enumerations;
using namespace ConfigConstants;

class ConfigurationManager {

public:
    explicit ConfigurationManager(const std::string &configurationFile);

    ConfigurationValues *getConfiguration();

private:
    // The source where the configuration will be read from
    ConfigurationValues *configuration;

    Document getJsonDocument(const std::string &filename);

    void config(rapidjson::Document &doc, const char *member, int &variable);
    void config(rapidjson::Document &doc, const char *member, long &variable);
    void config(rapidjson::Document &doc, const char *member, bool &variable);
    void config(rapidjson::Document &doc, const char *member, std::string &variable);
    void config(rapidjson::Document &doc, const char *member, EventType &variable);
};

#endif // CHRONOSQL_CONFIGURATIONMANAGER_H
