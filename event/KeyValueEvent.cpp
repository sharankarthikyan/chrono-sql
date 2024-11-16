#include "KeyValueEvent.h"

// Constructor that initializes with a payload and current timestamp
KeyValueEvent::KeyValueEvent(const char *payload_) 
    : Event(), payload(payload_) {}

// Constructor that initializes with a specific timestamp and payload
KeyValueEvent::KeyValueEvent(EID timestamp_, const char *payload_) 
    : Event(timestamp_), payload(payload_) {}

// Returns the payload
const char* KeyValueEvent::getPayload() const {
    return payload;
}
