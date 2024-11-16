//
// Created by pablo on 2/8/22.
//

#ifndef CHRONOSQL_UNRECOGNIZEDDAYOFTHEWEEK_H
#define CHRONOSQL_UNRECOGNIZEDDAYOFTHEWEEK_H

#include <exception>

class UnrecognizedDayOfTheWeek : public std::exception {

public:
    explicit UnrecognizedDayOfTheWeek();

    [[nodiscard]] const char* what() const noexcept override;
};

#endif // CHRONOSQL_UNRECOGNIZEDDAYOFTHEWEEK_H
