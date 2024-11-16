#include "Enumerations.h"

namespace Enumerations {
    // Definition of the EventTypeValues map
    const std::unordered_map<std::string, EventType> EventTypeValues = {
            {"FIXED_KEY_VALUE",   EventType::FIXED_KEY_VALUE},
            {"MEMORY_KEY_VALUE",  EventType::MEMORY_KEY_VALUE},
            {"INDEXED_KEY_VALUE", EventType::INDEXED_KEY_VALUE}
    };
}
