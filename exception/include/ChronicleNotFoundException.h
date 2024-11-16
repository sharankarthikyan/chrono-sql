//
// Created by pablo on 4/7/22.
//

#ifndef CHRONOSQL_CHRONICLENOTFOUNDEXCEPTION_H
#define CHRONOSQL_CHRONICLENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

class ChronicleNotFoundException : public std::exception {
    std::string chronicle;

public:
    [[nodiscard]] const char* what() const noexcept override;
};

#endif // CHRONOSQL_CHRONICLENOTFOUNDEXCEPTION_H
