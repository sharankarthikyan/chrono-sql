//
// Created by pablo on 26/7/22.
//

#ifndef CHRONOSQL_INVALIDWINDOWARGUMENT_H
#define CHRONOSQL_INVALIDWINDOWARGUMENT_H

#include <exception>

class InvalidWindowArgumentException : public std::exception {

public:
    explicit InvalidWindowArgumentException();

    [[nodiscard]] const char* what() const noexcept override;
};

#endif // CHRONOSQL_INVALIDWINDOWARGUMENT_H
