//
// Created by pablo on 17/05/2022.
//

#ifndef CHRONOSQL_KEYVALUEEVENT_H
#define CHRONOSQL_KEYVALUEEVENT_H

#include "Event.h"
#include "typedefs.h"

class KeyValueEvent : public Event {

public:
    explicit KeyValueEvent(const char *payload_);

    KeyValueEvent(EID timestamp_, const char *payload_);

    const char *getPayload() const;

private:
    const char *payload;
};

#endif // CHRONOSQL_KEYVALUEEVENT_H
