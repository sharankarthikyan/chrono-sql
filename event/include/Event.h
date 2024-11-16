//
// Created by pablo on 17/05/2022.
//

#ifndef CHRONOSQL_EVENT_H
#define CHRONOSQL_EVENT_H

#include <ctime>

class Event {

public:
    virtual ~Event();

    Event();

    explicit Event(std::time_t timestamp_);

    [[nodiscard]] std::time_t getTimestamp() const;

private:
    std::time_t timestamp;
};

#endif // CHRONOSQL_EVENT_H
