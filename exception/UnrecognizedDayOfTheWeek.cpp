#include "UnrecognizedDayOfTheWeek.h"

UnrecognizedDayOfTheWeek::UnrecognizedDayOfTheWeek() : std::exception() {}

const char* UnrecognizedDayOfTheWeek::what() const noexcept {
    return "Equals parameter is not valid. Please, use a timestamp or a day of the week";
}
