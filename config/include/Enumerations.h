//
// Created by pablo on 21/05/2022.
//

#ifndef CHRONOSQL_ENUMERATIONS_H
#define CHRONOSQL_ENUMERATIONS_H

#include <unordered_map>
#include <string>

namespace Enumerations {

    // Enum to determine the type of events that will be generated
    enum class EventType {
        FIXED_KEY_VALUE, MEMORY_KEY_VALUE, INDEXED_KEY_VALUE
    };

    enum class DayOfTheWeek {
        SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
    };

    // Declaration of the EventTypeValues map (definition will be in Enumerations.cpp)
    extern const std::unordered_map<std::string, EventType> EventTypeValues;
}

#endif // CHRONOSQL_ENUMERATIONS_H
