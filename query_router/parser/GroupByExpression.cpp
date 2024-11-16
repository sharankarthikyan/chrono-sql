#include "GroupByExpression.h"

// Constructor implementation
GroupByExpression::GroupByExpression(std::string _name, std::string _alias)
    : name(std::move(_name)), alias(std::move(_alias)), expression(nullptr) {}
