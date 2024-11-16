//
// Created by pablo on 17/05/2022.
//

#ifndef ChronoSQL_EVENTGENERATOR_H
#define ChronoSQL_EVENTGENERATOR_H

#include <cstring>
#include <random>
#include <list>
#include "Event.h"

class EventGenerator {

public:
    [[nodiscard]] virtual Event *generateEvent() const;

    [[nodiscard]] virtual Event *generateEvent(int size) const;

    [[nodiscard]] virtual std::list<Event *> generateEvents(int nEvents) const;

    [[nodiscard]] const char *generateRandomBytes(int size) const;

protected:
    const char charset[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
};

#endif //ChronoSQL_EVENTGENERATOR_H
