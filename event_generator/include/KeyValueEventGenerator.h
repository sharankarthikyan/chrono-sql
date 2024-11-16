//
// Created by pablo on 17/05/2022.
//

#ifndef ChronoSQL_KEYVALUEEVENTGENERATOR_H
#define ChronoSQL_KEYVALUEEVENTGENERATOR_H

#include "EventGenerator.h"
#include "KeyValueEvent.h"

class KeyValueEventGenerator : public EventGenerator {

public:
    explicit KeyValueEventGenerator(int _payloadSize, int _payloadVariation, EID _lowerTimestamp, EID _higherTimestamp);

    [[nodiscard]] Event *generateEvent() const override;

    [[nodiscard]] Event *generateEvent(int size) const override;

    [[nodiscard]] std::list<Event *> generateEvents(int nEvents) const override;

    [[nodiscard]] EID generateRandomEID() const;

private:
    int payloadSize;
    int payloadVariation;
    EID lowerTimestamp;
    EID higherTimestamp;
};

#endif //ChronoSQL_KEYVALUEEVENTGENERATOR_H
