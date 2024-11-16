#include "IndexedEventReader.h"
#include "MemoryIndex.h"
#include "Constants.h"

IndexedEventReader::IndexedEventReader(int _fixedPayloadSize) : DiskEventReader(_fixedPayloadSize) {}

std::list<std::pair<EID, const char *>> *
IndexedEventReader::readEventsInRange(const CID &cid, std::time_t start, std::time_t end) {
    // Determine the starting position using MemoryIndex if a start time is specified
    long i = (start == VOID_TIMESTAMP) ? 0 : MemoryIndex::getClosestValue(cid, start);

    // Use DiskEventReader's method to read events within the specified range
    return DiskEventReader::readEventsInRange(cid + Constants::LOG_EXTENSION, i, start, end);
}
