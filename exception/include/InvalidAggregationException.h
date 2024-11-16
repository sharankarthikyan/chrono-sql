//
// Created by pablo on 28/7/22.
//

#ifndef CHRONOSQL_INVALIDAGGREGATIONEXCEPTION_H
#define CHRONOSQL_INVALIDAGGREGATIONEXCEPTION_H

#include <exception>

class InvalidAggregationException : public std::exception {

public:
    explicit InvalidAggregationException();

    [[nodiscard]] const char* what() const noexcept override;
};

#endif // CHRONOSQL_INVALIDAGGREGATIONEXCEPTION_H
