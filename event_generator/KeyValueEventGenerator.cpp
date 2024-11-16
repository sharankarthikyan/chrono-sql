#include "KeyValueEventGenerator.h"
#include <random>

// Constructor definition
KeyValueEventGenerator::KeyValueEventGenerator(int _payloadSize, int _payloadVariation, EID _lowerTimestamp, EID _higherTimestamp)
        : payloadSize(_payloadSize), payloadVariation(_payloadVariation), lowerTimestamp(_lowerTimestamp),
          higherTimestamp(_higherTimestamp) {
}

// Generates an event with the default payload size
Event *KeyValueEventGenerator::generateEvent() const {
    return generateEvent(payloadSize);
}

// Generates an event with a specific payload size
Event *KeyValueEventGenerator::generateEvent(int size) const {
    return new KeyValueEvent(generateRandomEID(), generateRandomBytes(size));
}

// Generates a list of events, each with a random EID and payload size
std::list<Event *> KeyValueEventGenerator::generateEvents(int nEvents) const {
    std::list<Event *> events;
    std::mt19937 rg{std::random_device{}()};
    std::uniform_int_distribution<long> pick(lowerTimestamp, higherTimestamp);

    for (int i = 0; i < nEvents; i++) {
        events.push_back(new KeyValueEvent(pick(rg), generateRandomBytes(payloadSize)));
    }
    return events;
}

// Generates a random EID within the given timestamp range
EID KeyValueEventGenerator::generateRandomEID() const {
    std::mt19937 rg{std::random_device{}()};
    std::uniform_int_distribution<long> pick(lowerTimestamp, higherTimestamp);
    return pick(rg);
}
