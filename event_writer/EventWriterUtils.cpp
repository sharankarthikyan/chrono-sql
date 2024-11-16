#include "EventWriterUtils.h"
#include <cstring>

EventWriterUtils::EventWriterUtils(int _fixedPayloadSize) : fixedPayloadSize(_fixedPayloadSize) {}

std::string EventWriterUtils::trimByteSequence(const char *payload) const {
    int receivedSize = strlen(payload);

    if (receivedSize == fixedPayloadSize) {
        return std::string(payload, receivedSize); // Return as-is if sizes match
    }

    std::string trimmed;
    trimmed.reserve(fixedPayloadSize);

    if (receivedSize < fixedPayloadSize) {
        // Copy payload and pad with spaces to reach the fixed size
        trimmed.assign(payload, receivedSize);
        trimmed.append(fixedPayloadSize - receivedSize, ' ');
    } else {
        // Copy only up to the fixed payload size
        trimmed.assign(payload, fixedPayloadSize);
    }

    return trimmed;
}
