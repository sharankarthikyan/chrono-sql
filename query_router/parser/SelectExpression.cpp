#include "SelectExpression.h"

SelectExpression *SelectExpression::starExpression() {
    auto *expr = new SelectExpression();
    expr->isStar = true;
    expr->type = hsql::kExprStar;
    return expr;
}

SelectExpression *SelectExpression::functionExpression(std::string name, const char *alias) {
    auto *expr = new SelectExpression();
    expr->type = hsql::kExprFunctionRef;
    expr->isFunction = true;
    expr->name = std::move(name);
    expr->nestedExpressions = new std::vector<SelectExpression *>;

    if (alias != nullptr) {
        expr->alias = std::string(alias);
        expr->isAliased = true;
    }

    return expr;
}

SelectExpression *SelectExpression::columnExpression(std::string name) {
    auto *expr = new SelectExpression();
    expr->type = hsql::kExprColumnRef;
    expr->isColumn = true;
    expr->name = std::move(name);
    return expr;
}

SelectExpression *SelectExpression::stringExpression(std::string name) {
    auto *expr = new SelectExpression();
    expr->type = hsql::kExprLiteralString;
    expr->isColumn = false;
    expr->name = std::move(name);
    return expr;
}

SelectExpression *SelectExpression::intervalExpression(long value, hsql::DatetimeField dt) {
    auto *expr = new SelectExpression();
    expr->type = hsql::kExprLiteralInterval;
    expr->value = value;
    expr->dateTime = dt;
    return expr;
}
