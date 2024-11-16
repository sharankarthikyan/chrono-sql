#include "ConditionExpression.h"

// Constructor for integer condition
ConditionExpression::ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, long _intValue)
    : operatorType(_operatorType), fieldName(std::move(_fieldName)), intValue(_intValue) {
    type = ConditionType::INT;
}

// Constructor for double condition
ConditionExpression::ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, double _doubleValue)
    : operatorType(_operatorType), fieldName(std::move(_fieldName)), doubleValue(_doubleValue) {
    type = ConditionType::DOUBLE;
}

// Constructor for string condition
ConditionExpression::ConditionExpression(hsql::OperatorType _operatorType, std::string _fieldName, std::string _stringValue)
    : operatorType(_operatorType), fieldName(std::move(_fieldName)), stringValue(std::move(_stringValue)) {
    type = ConditionType::STRING;
}
