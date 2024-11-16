#include "KeyValueEventGeneratorFactory.h"

// Constructor implementation
KeyValueEventGeneratorFactory::KeyValueEventGeneratorFactory(const ConfigurationValues *config)
    : payloadSize(config->payloadSize),
      payloadVariation(config->payloadVariation),
      lowerTimestamp(config->lowerTimestamp),
      higherTimestamp(config->higherTimestamp) {
}

// getGenerator method implementation
EventGenerator *KeyValueEventGeneratorFactory::getGenerator() const {
    return new KeyValueEventGenerator(payloadSize, payloadVariation, lowerTimestamp, higherTimestamp);
}
