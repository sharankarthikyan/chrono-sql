//
// Created by pablo on 18/05/2022.
//

#ifndef ChronoSQL_KEYVALUEEVENTGENERATORFACTORY_H
#define ChronoSQL_KEYVALUEEVENTGENERATORFACTORY_H

#include "EventGeneratorFactory.h"
#include "KeyValueEventGenerator.h"
#include "ConfigurationManager.h"

class KeyValueEventGeneratorFactory {
public:
    explicit KeyValueEventGeneratorFactory(const ConfigurationValues *config);

    [[nodiscard]] EventGenerator *getGenerator() const;

private:
    int payloadSize;
    int payloadVariation;
    long lowerTimestamp;
    long higherTimestamp;
};

#endif //ChronoSQL_KEYVALUEEVENTGENERATORFACTORY_H
