#include "FieldNotFoundException.h"
#include <utility>

FieldNotFoundException::FieldNotFoundException(std::string field_) 
    : field(std::move(field_)) {}

const char* FieldNotFoundException::what() const noexcept {
    return "Field not found";
}

std::string FieldNotFoundException::getField() {
    return field;
}
