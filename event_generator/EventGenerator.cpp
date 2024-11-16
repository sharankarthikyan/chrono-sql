#include "EventGenerator.h"

Event *EventGenerator::generateEvent() const {
    return nullptr;
}

Event *EventGenerator::generateEvent(int size) const {
    return nullptr;
}

std::list<Event *> EventGenerator::generateEvents(int nEvents) const {
    return {};
}

const char *EventGenerator::generateRandomBytes(int size) const {
    char *result = new char[size + 1];  // +1 to reserve space for the null terminating char

    // Random generator
    std::mt19937 rg{std::random_device{}()};
    std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(charset) - 2);

    for (int i = 0; i < size; i++) {
        result[i] = charset[pick(rg)];
    }
    result[size] = '\0';

    return result;
}
