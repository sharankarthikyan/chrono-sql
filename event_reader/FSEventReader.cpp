#include "FSEventReader.h"
#include "DiskEventReader.h"
#include "Constants.h"

FSEventReader::FSEventReader(int fixedPayloadSize_) : DiskEventReader(fixedPayloadSize_) {}

std::list<std::pair<EID, const char *>> *
FSEventReader::readEventsInRange(const CID &cid, std::time_t start, std::time_t end) {
    return DiskEventReader::readEventsInRange(cid + Constants::LOG_EXTENSION, 0, start, end);
}
