#include "FSKeyValueEventWriter.h"

// Constructor
FSKeyValueEventWriter::FSKeyValueEventWriter(int _fixedPayloadSize) : fixedPayloadSize(_fixedPayloadSize) {
    writerUtils = new EventWriterUtils(_fixedPayloadSize);
}

// Writes a single event to the output file
int FSKeyValueEventWriter::write(const CID &cid, Event *event) {
    KeyValueEvent *kvEvent = toKeyValue(event);
    if (kvEvent != nullptr) {
        std::ofstream outputFile = openWriteFile(cid + LOG_EXTENSION);
        writeToOutputFile(outputFile, kvEvent->getTimestamp(), kvEvent->getPayload());
        outputFile.close();
        return 0;
    }

    return 1;
}

// Writes a list of events to the output file
int FSKeyValueEventWriter::write(const CID &cid, std::list<Event *> events) {
    std::ofstream outputFile = openWriteFile(cid + LOG_EXTENSION);
    for (auto const i : events) {
        KeyValueEvent *kvEvent = toKeyValue(i);
        if (kvEvent != nullptr) {
            writeToOutputFile(outputFile, kvEvent->getTimestamp(), kvEvent->getPayload());
        }
    }
    outputFile.close();

    return 0;
}

// Helper to cast Event to KeyValueEvent
KeyValueEvent* FSKeyValueEventWriter::toKeyValue(Event *event) {
    return dynamic_cast<KeyValueEvent *>(event);
}

// Writes a timestamp and payload to the output file
void FSKeyValueEventWriter::writeToOutputFile(std::ofstream &outFile, std::time_t timestamp, const char *payload) {
    outFile << timestamp << ',' << writerUtils->trimByteSequence(payload) << ';';
}
