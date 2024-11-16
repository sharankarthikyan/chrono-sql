#include "EventGeneratorFactory.h"

EventGenerator *EventGeneratorFactory::getGenerator(const ConfigurationValues *config) {
    if (config->eventType == EventType::FIXED_KEY_VALUE || config->eventType == EventType::INDEXED_KEY_VALUE) {
        auto *kvGeneratorFactory = new KeyValueEventGeneratorFactory(config);
        return kvGeneratorFactory->getGenerator();
    } else {
        return nullptr;
    }
}
