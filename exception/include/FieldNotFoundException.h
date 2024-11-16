//
// Created by pablo on 4/7/22.
//

#ifndef CHRONOSQL_FIELDNOTFOUNDEXCEPTION_H
#define CHRONOSQL_FIELDNOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

class FieldNotFoundException : public std::exception {

    std::string field;

public:
    explicit FieldNotFoundException(std::string field_);
    
    [[nodiscard]] const char* what() const noexcept override;

    std::string getField();
};

#endif // CHRONOSQL_FIELDNOTFOUNDEXCEPTION_H
