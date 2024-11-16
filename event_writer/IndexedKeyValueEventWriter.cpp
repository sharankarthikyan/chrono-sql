#include "IndexedKeyValueEventWriter.h"
#include <fstream>
#include <cmath>

// Constructor initializes fixed payload size and index interval
IndexedKeyValueEventWriter::IndexedKeyValueEventWriter(int _fixedPayloadSize, int _indexIntervalBytes)
        : fixedPayloadSize(_fixedPayloadSize), indexIntervalBytes(_indexIntervalBytes) {
    writerUtils = new EventWriterUtils(_fixedPayloadSize);
}

// Writes a single event to the output file and updates the index
int IndexedKeyValueEventWriter::write(const CID &cid, Event *event) {
    auto *kvEvent = dynamic_cast<KeyValueEvent *>(event);
    if (kvEvent != nullptr) {
        std::ofstream outputFile = openWriteFile(cid + LOG_EXTENSION);
        writeToOutputFile(outputFile, kvEvent->getTimestamp(), kvEvent->getPayload());
        outputFile.close();

        updateIndex(cid, kvEvent);
        return 0;
    }
    return 1;
}

// Writes multiple events to the output file and updates the index for each
int IndexedKeyValueEventWriter::write(const CID &cid, std::list<Event *> events) {
    std::ofstream outputFile = openWriteFile(cid + LOG_EXTENSION);
    for (auto const &i : events) {
        auto *kvEvent = dynamic_cast<KeyValueEvent *>(i);
        if (kvEvent != nullptr) {
            writeToOutputFile(outputFile, kvEvent->getTimestamp(), kvEvent->getPayload());
            updateIndex(cid, kvEvent);
        }
    }
    outputFile.close();
    return 1;
}

// Helper function to write timestamp and payload to the output file
void IndexedKeyValueEventWriter::writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, const char *payload) {
    outFile << timestamp << ',' << writerUtils->trimByteSequence(payload) << ';';
}

// Overloaded function to write timestamp and byte count to the index file
void IndexedKeyValueEventWriter::writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, long byteCount) {
    outFile << timestamp << ',' << byteCount << ';';
}

// Updates the memory index based on index interval and writes to the index file if needed
void IndexedKeyValueEventWriter::updateIndex(const CID &cid, KeyValueEvent *kvEvent) {
    int eventSize = fixedPayloadSize + getNumberOfDigits(kvEvent->getTimestamp()) + 2;
    if (currentByteCount + eventSize >= indexIntervalBytes) {
        MemoryIndex::addEntry(cid, kvEvent->getTimestamp(), totalByteCount);
        std::ofstream outputIndexFile = openWriteFile(cid + INDEX_EXTENSION);
        writeToOutputFile(outputIndexFile, kvEvent->getTimestamp(), totalByteCount);
        outputIndexFile.close();
        currentByteCount = 0;
    } else {
        currentByteCount += eventSize;
    }
    totalByteCount += eventSize;
}

// Helper function to get the number of digits in a long integer
int IndexedKeyValueEventWriter::getNumberOfDigits(long i) {
    return i > 0 ? static_cast<int>(log10(static_cast<double>(i)) + 1) : 1;
}
