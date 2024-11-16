// ConditionExpression.h

#ifndef CONDITIONEXPRESSION_H
#define CONDITIONEXPRESSION_H

#include <string>
#include "SQLParser.h"

enum class ConditionType {
    INT, DOUBLE, STRING
};

class ConditionExpression {
public:
    hsql::OperatorType operatorType;
    ConditionType type;
    std::string fieldName;
    long intValue;
    double doubleValue;
    std::string stringValue;

    // Constructors for different data types
    ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, long _intValue);
    ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, double _doubleValue);
    ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, std::string _stringValue);
};

#endif //CONDITIONEXPRESSION_H
