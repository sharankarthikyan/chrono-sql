#include "ConfigurationManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

ConfigurationManager::ConfigurationManager(const std::string &configurationFile) {
    configuration = new ConfigurationValues();
    Document configDoc = getJsonDocument(configurationFile);
    config(configDoc, NUMBER_EVENTS, configuration->nEvents);
    config(configDoc, EVENT_TYPE, configuration->eventType);
    config(configDoc, OUTPUT_FILE, configuration->outputFile);
    config(configDoc, LOWER_TIMESTAMP, configuration->lowerTimestamp);
    config(configDoc, HIGHER_TIMESTAMP, configuration->higherTimestamp);

    if (configuration->eventType == EventType::FIXED_KEY_VALUE ||
        configuration->eventType == EventType::MEMORY_KEY_VALUE ||
        configuration->eventType == EventType::INDEXED_KEY_VALUE) {
        config(configDoc, PAYLOAD_SIZE, configuration->payloadSize);
        config(configDoc, PAYLOAD_VARIATION, configuration->payloadVariation);
        config(configDoc, FIXED_PAYLOAD_SIZE, configuration->fixedPayloadSize);

        if (configuration->eventType == EventType::INDEXED_KEY_VALUE) {
            config(configDoc, INDEX_INTERVAL_BYTES, configuration->indexIntervalBytes);
        }
    }

    // Testing config
    config(configDoc, HIDE_OUTPUT, configuration->hideOutput);
    config(configDoc, N_EXECUTIONS, configuration->nExecutions);
    config(configDoc, SQL_FILE_PATH, configuration->sqlFilePath);
}

ConfigurationValues* ConfigurationManager::getConfiguration() {
    return configuration;
}

Document ConfigurationManager::getJsonDocument(const std::string &filename) {
    // open the JSON file
    std::ifstream jFile(filename);
    if (!jFile.is_open()) {
        std::cerr << "Unable to open configuration file " << filename << std::endl;
        exit(-1);
    }

    // read the file contents
    std::stringstream contents;
    contents << jFile.rdbuf();

    rapidjson::Document doc;
    doc.Parse(contents.str().c_str());  // parse the JSON from the string contents
    return doc;
}

void ConfigurationManager::config(rapidjson::Document &doc, const char *member, int &variable) {
    assert(doc.HasMember(member));
    assert(doc[member].IsInt());
    variable = doc[member].GetInt();
}

void ConfigurationManager::config(rapidjson::Document &doc, const char *member, long &variable) {
    assert(doc.HasMember(member));
    assert(doc[member].IsInt64());
    variable = doc[member].GetInt64();
}

void ConfigurationManager::config(rapidjson::Document &doc, const char *member, bool &variable) {
    assert(doc.HasMember(member));
    assert(doc[member].IsInt());
    variable = doc[member].GetInt() > 0;
}

void ConfigurationManager::config(rapidjson::Document &doc, const char *member, std::string &variable) {
    assert(doc.HasMember(member));
    assert(doc[member].IsString());
    variable = doc[member].GetString();
}

void ConfigurationManager::config(rapidjson::Document &doc, const char *member, EventType &variable) {
    assert(doc.HasMember(member));
    assert(doc[member].IsString());
    variable = EventTypeValues.find(doc[member].GetString())->second;
}
