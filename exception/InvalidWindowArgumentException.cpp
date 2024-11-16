#include "InvalidWindowArgumentException.h"

InvalidWindowArgumentException::InvalidWindowArgumentException() : std::exception() {}

const char* InvalidWindowArgumentException::what() const noexcept {
    return "Invalid provided argument to the window function. Accepted format: <n> <date_expression>";
}
