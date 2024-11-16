#include "ChronicleNotFoundException.h"

const char* ChronicleNotFoundException::what() const noexcept {
    return "Chronicle not found";
}
