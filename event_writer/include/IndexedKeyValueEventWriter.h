//
// Created by pablo on 26/05/2022.
//

#ifndef CHRONOSQL_INDEXEDKEYVALUEEVENTWRITER_H
#define CHRONOSQL_INDEXEDKEYVALUEEVENTWRITER_H

#include <iostream>
#include <list>
#include "EventWriter.h"
#include "Constants.h"
#include "KeyValueEvent.h"
#include "EventWriterUtils.h"
#include "MemoryIndex.h"

using namespace Constants;

class IndexedKeyValueEventWriter : public EventWriter {

public:
    IndexedKeyValueEventWriter(int _fixedPayloadSize, int _indexIntervalBytes);

    int write(const CID &cid, Event *event) override;

    int write(const CID &cid, std::list<Event *> events) override;

private:
    const int fixedPayloadSize;
    long currentByteCount = 0;
    long totalByteCount = 0;
    long indexIntervalBytes;
    EventWriterUtils *writerUtils;

    void writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, const char *payload);

    void writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, long byteCount);

    void updateIndex(const CID &cid, KeyValueEvent *kvEvent);

    static int getNumberOfDigits(long i);
};

#endif // CHRONOSQL_INDEXEDKEYVALUEEVENTWRITER_H
