#include "Event.h"

// Default constructor initializes timestamp to current time
Event::Event() : timestamp(std::time(nullptr)) {}

// Parameterized constructor to set a specific timestamp
Event::Event(std::time_t timestamp_) : timestamp(timestamp_) {}

// Destructor
Event::~Event() = default;

// Returns the timestamp
std::time_t Event::getTimestamp() const {
    return timestamp;
}
