// SelectExpression.h
#ifndef SELECTEXPRESSION_H
#define SELECTEXPRESSION_H

#include <string>
#include <vector>
#include "SQLParser.h"

class SelectExpression {
public:
    hsql::ExprType type;
    bool isStar;
    bool isFunction;
    bool isColumn;
    bool isAliased;
    long value;
    hsql::DatetimeField dateTime;
    std::string name;
    std::string alias;
    std::vector<SelectExpression *> *nestedExpressions;

    static SelectExpression *starExpression();
    static SelectExpression *functionExpression(std::string name, const char *alias);
    static SelectExpression *columnExpression(std::string name);
    static SelectExpression *stringExpression(std::string name);
    static SelectExpression *intervalExpression(long value, hsql::DatetimeField dt);
};

#endif // SELECTEXPRESSION_H
