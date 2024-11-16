// EventInterval.cpp

#include "EventInterval.h"

EventInterval::EventInterval() {
    startEID = VOID_TIMESTAMP;
    endEID = VOID_TIMESTAMP;
    days = std::list<Enumerations::DayOfTheWeek>();
}
