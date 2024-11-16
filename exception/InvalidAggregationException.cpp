#include "InvalidAggregationException.h"

InvalidAggregationException::InvalidAggregationException() : std::exception() {}

const char* InvalidAggregationException::what() const noexcept {
    return "Aggregation function is not supported. Supported aggregation functions: {COUNT, WINDOW}";
}
