//
// Created by pablo on 18/05/2022.
//

#ifndef ChronoSQL_EVENTGENERATORFACTORY_H
#define ChronoSQL_EVENTGENERATORFACTORY_H

#include "EventGenerator.h"
#include "ConfigurationManager.h"
#include "KeyValueEventGeneratorFactory.h"

class EventGeneratorFactory {

public:
    [[nodiscard]] EventGenerator *getGenerator(const ConfigurationValues *config);
};

#endif //ChronoSQL_EVENTGENERATORFACTORY_H
