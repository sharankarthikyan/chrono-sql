// EventInterval.h

#ifndef EVENTINTERVAL_H
#define EVENTINTERVAL_H

#include <list>
#include "typedefs.h"
#include "Constants.h"
#include "Enumerations.h"

class EventInterval {
public:
    EID startEID;
    EID endEID;
    std::list<Enumerations::DayOfTheWeek> days;

    EventInterval();  // Constructor prototype
};

#endif //EVENTINTERVAL_H
