//
// Created by pablo on 4/8/22.
//

#ifndef CHRONOSQL_EVENTWRITERUTILS_H
#define CHRONOSQL_EVENTWRITERUTILS_H

#include <string>

class EventWriterUtils {

public:
    explicit EventWriterUtils(int _fixedPayloadSize);

    // Returns a trimmed or padded copy of the payload
    std::string trimByteSequence(const char *payload) const;

private:
    int fixedPayloadSize;
};

#endif // CHRONOSQL_EVENTWRITERUTILS_H
