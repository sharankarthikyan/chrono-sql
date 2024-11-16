// GroupByExpression.h

#ifndef GROUPBYEXPRESSION_H
#define GROUPBYEXPRESSION_H

#include <string>
#include "SQLParser.h"
#include "SelectExpression.h"

class GroupByExpression {
public:
    std::string name;
    std::string alias;
    SelectExpression *expression;

    // Constructor
    GroupByExpression(std::string _name, std::string _alias);
};

#endif // GROUPBYEXPRESSION_H
