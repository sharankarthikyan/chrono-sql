#include "ChronoSQLParser.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include "SQLParser.h"
#include "SQLParserResult.h"
#include "SelectExpression.h"
#include "ChronoLog.h"
#include "WorkerClient.h"
#include "document.h"
#include "error/en.h"

bool hideOutput;
ChronoLog *chronoLog;
std::vector<WorkerClient> worker_clients_;
std::mt19937 rng_;
std::uniform_int_distribution<> dist_;

// Initialize static variables
std::unordered_map<hsql::DatetimeField, long> ChronoSQLParser::intervalConversions = {
    {hsql::kDatetimeSecond, 1}, {hsql::kDatetimeMinute, 60},
    {hsql::kDatetimeHour, 3600}, {hsql::kDatetimeDay, 86400},
    {hsql::kDatetimeMonth, 2626288}, {hsql::kDatetimeYear, 31536000}
};

std::unordered_map<std::string, Enumerations::DayOfTheWeek> ChronoSQLParser::daysOfTheWeek = {
    {"SUNDAY", Enumerations::DayOfTheWeek::SUNDAY}, {"MONDAY", Enumerations::DayOfTheWeek::MONDAY},
    {"TUESDAY", Enumerations::DayOfTheWeek::TUESDAY}, {"WEDNESDAY", Enumerations::DayOfTheWeek::WEDNESDAY},
    {"THURSDAY", Enumerations::DayOfTheWeek::THURSDAY}, {"FRIDAY", Enumerations::DayOfTheWeek::FRIDAY},
    {"SATURDAY", Enumerations::DayOfTheWeek::SATURDAY}
};

std::vector<std::string> ChronoSQLParser::ReadServerAddresses(const std::string& filename) {
    std::vector<std::string> servers;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open server configuration file: " << filename << std::endl;
        return servers;
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    ifs.close();

    rapidjson::Document doc;
    rapidjson::ParseResult parseResult = doc.Parse(content.c_str());
    if (!parseResult) {
        std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code())
                  << " (offset " << parseResult.Offset() << ")" << std::endl;
        return servers;
    }

    if (!doc.HasMember("worker_servers") || !doc["worker_servers"].IsArray()) {
        std::cerr << "Invalid server configuration format." << std::endl;
        return servers;
    }

    for (const auto& server : doc["worker_servers"].GetArray()) {
        if (server.IsString()) {
            servers.emplace_back(server.GetString());
        } else {
            std::cerr << "Invalid server address format in configuration." << std::endl;
        }
    }

    return servers;
}

ChronoSQLParser::ChronoSQLParser(ConfigurationValues *config, const std::string& filename) {
    chronoLog = new ChronoLog(config);
    hideOutput = config->hideOutput;
    std::vector<std::string> addresses = ReadServerAddresses(filename);

    for (const auto& address : addresses) {
        worker_clients_.emplace_back(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));
    }

    if (worker_clients_.empty()) {
        throw std::runtime_error("No worker nodes available.");
    }

    rng_ = std::mt19937(std::random_device{}());
    dist_ = std::uniform_int_distribution<>(0, worker_clients_.size() - 1);
}

std::unique_ptr<std::list<std::pair<EID, std::string>>> ChronoSQLParser::getReplayDataFromWorker(const std::string& cid, int64_t startEID, int64_t endEID) {
    int retries = worker_clients_.size();

    while (retries-- > 0) {
        int index = dist_(rng_);
        try {
            // Fetch results from the worker
            auto results = worker_clients_[index].getReplayData(cid, startEID, endEID);

            // Convert std::vector to std::list
            auto result_list = std::make_unique<std::list<std::pair<EID, std::string>>>();
            for (const auto& result : results) {
                result_list->emplace_back(result.first, result.second);
            }

            return result_list;
        } catch (const std::exception& e) {
            std::cerr << "Worker " << index << " failed: " << e.what() << std::endl;
        }
    }

    throw std::runtime_error("All workers failed.");
}

void ChronoSQLParser::parse(const std::string& query, QueryResponse* response) {
    hsql::SQLParserResult result;
    hsql::SQLParser::parse(query, &result);

    if (result.isValid()) {
        for (int i = 0; i < result.size(); i++) {
            const hsql::SQLStatement* statement = result.getStatement(i);
            if (statement->isType(hsql::kStmtSelect)) {
                parseSelectStatement(static_cast<const hsql::SelectStatement*>(statement), response);
            }
            else {
                response->set_result("Unsupported statement. Supported statements: {SELECT}.");
            }
        }
    } else {
        response->set_result("Error parsing statement: " + std::string(result.errorMsg()));
    }
}

std::unique_ptr<EventInterval> ChronoSQLParser::extractInterval(const std::list<ConditionExpression*>* conditions) {
    auto interval = std::make_unique<EventInterval>();

    if (conditions != nullptr && !conditions->empty()) {
        for (auto cond : *conditions) {
            if (cond->fieldName == "EID") {
                if (cond->operatorType == hsql::kOpGreater) {
                    interval->startEID = cond->intValue + 1;
                }
                else if (cond->operatorType == hsql::kOpGreaterEq) {
                    interval->startEID = cond->intValue;
                }
                else if (cond->operatorType == hsql::kOpLess) {
                    interval->endEID = cond->intValue - 1;
                }
                else if (cond->operatorType == hsql::kOpLessEq) {
                    interval->endEID = cond->intValue;
                }
                else if (cond->operatorType == hsql::kOpEquals) {
                    if (cond->stringValue.empty()) {
                        interval->startEID = cond->intValue;
                        interval->endEID = cond->intValue;
                    }
                    else {
                        std::transform(cond->stringValue.begin(), cond->stringValue.end(),
                                       cond->stringValue.begin(), ::toupper);
                        if (daysOfTheWeek.count(cond->stringValue)) {
                            interval->days.push_back(daysOfTheWeek[cond->stringValue]);
                        }
                        else {
                            throw UnrecognizedDayOfTheWeek();
                        }
                    }
                }
            }
            else {
                throw FieldNotFoundException(cond->fieldName);
            }
        }
    }
    return interval;
}

void ChronoSQLParser::printResults(std::unique_ptr<std::list<std::pair<EID, std::string>>> events,
                                   std::unordered_map<std::string, std::string> aliases,
                                   std::unique_ptr<std::list<GroupByExpression*>> groupBy,
                                   QueryResponse* response) {
    std::string result_output;
    int i = 0, isAggregate = 0, isWindow = 0;

    if (!events->empty() &&
        (SUPPORTED_FUNCTIONS.count(events->front().second) ||
         SUPPORTED_FUNCTIONS.count(aliases[events->front().second]))) {
        isAggregate = 1;
        isWindow = (events->front().second == "WINDOW") || aliases[events->front().second] == "WINDOW";

        result_output += events->front().second + "\n";
        events->pop_front();
    }

    result_output += "----------\n";
    for (const auto& event : *events) {
        std::string windowValue = isWindow ? std::to_string(event.first) + "     " : "";
        result_output += windowValue + event.second + "\n";
        i++;
    }

    if (!isAggregate) {
        result_output += "(" + std::to_string(i) + " events)\n";
    }

    response->set_result(result_output);

    // No need to delete anything; unique_ptr will automatically handle memory
}

SelectExpression* ChronoSQLParser::parseSelectToken(hsql::Expr* expr, std::unordered_map<std::string, std::string>& aliases) {
    if (expr->type == hsql::kExprStar) {
        return SelectExpression::starExpression();
    }
    else if (expr->type == hsql::kExprColumnRef) {
        std::cout << " field " << expr->name;
        return SelectExpression::columnExpression(expr->name);
    }
    else if (expr->type == hsql::kExprFunctionRef) {
        auto* function = SelectExpression::functionExpression(expr->name, expr->alias);

        if (expr->hasAlias()) {
            aliases[expr->alias] = expr->name;
        }

        for (hsql::Expr* e : *expr->exprList) {
            // Do the same for each inner expression
            function->nestedExpressions->push_back(parseSelectToken(e, aliases));
        }
        return function;
    }
    else if (expr->type == hsql::kExprLiteralString) {
        return SelectExpression::stringExpression(expr->name);
    }
    else if (expr->type == hsql::kExprLiteralInterval) {
        return SelectExpression::intervalExpression(expr->ival, expr->datetimeField);
    }
    else {
        std::cout << "Found unsupported select expression" << std::endl;
        return nullptr;
    }
}

std::list<ConditionExpression*>* ChronoSQLParser::parseWhereExpression(const hsql::Expr* expression) {
    if (expression->opType == hsql::kOpAnd || expression->opType == hsql::kOpOr) {
        // Evaluate individual clauses
        std::list<ConditionExpression*>* expr1 = parseWhereExpression(expression->expr);
        std::list<ConditionExpression*>* expr2 = parseWhereExpression(expression->expr2);
        expr1->splice(expr1->end(), *expr2);
        return expr1;
    }

    if (expression->opType == hsql::kOpEquals || expression->opType == hsql::kOpNotEquals ||
        expression->opType == hsql::kOpLess || expression->opType == hsql::kOpGreater ||
        expression->opType == hsql::kOpLessEq || expression->opType == hsql::kOpGreaterEq) {
        auto* result = new std::list<ConditionExpression*>;
        if (expression->expr2->type == hsql::kExprLiteralInt) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr->name,
                                            static_cast<long>(expression->expr2->ival)));
        }
        else if (expression->expr2->type == hsql::kExprLiteralFloat) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr->name,
                                            expression->expr2->fval));
        }
        else if (expression->expr2->type == hsql::kExprLiteralString) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr->name,
                                            expression->expr2->name));
        }
        else if (expression->expr->type == hsql::kExprLiteralInt) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr2->name,
                                            static_cast<long>(expression->ival)));
        }
        else if (expression->expr->type == hsql::kExprLiteralFloat) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr2->name,
                                            expression->fval));
        }
        else if (expression->expr->type == hsql::kExprLiteralString) {
            result->push_back(
                    new ConditionExpression(expression->opType, expression->expr2->name,
                                            expression->name));
        }
        return result;
    }

    return nullptr;
}

std::unique_ptr<std::list<GroupByExpression*>>
ChronoSQLParser::parseGroupBy(hsql::GroupByDescription* groupBy, std::unordered_map<std::string, std::string> aliases) {
    auto result = std::make_unique<std::list<GroupByExpression*>>();
    for (hsql::Expr* expr : *groupBy->columns) {
        std::string name = expr->name;
        std::string alias;
        if (aliases.count(name)) {
            name = aliases[name];
            alias = expr->name;
        }
        result->push_back(new GroupByExpression(name, alias));
    }
    return result;
}

std::unique_ptr<std::list<std::pair<EID, std::string>>>
ChronoSQLParser::executeExpressions(const CID& cid, std::vector<SelectExpression*>* expressions,
                   const std::list<ConditionExpression*>* conditions,
                   std::list<GroupByExpression*>* groupBy,
                   std::unordered_map<std::string, std::string>& aliases) {
    for (SelectExpression* e : *expressions) {
        if (e->isStar) {
            auto interval = extractInterval(conditions);
            if (interval->days.empty()) {
                return getReplayDataFromWorker(cid, interval->startEID, interval->endEID);
            }
            else {
                auto events = getReplayDataFromWorker(cid, interval->startEID, interval->endEID);
                auto value = std::make_unique<std::list<std::pair<EID, std::string>>>();
                for (const auto& ev : *events) {
                    if (eventMeetsDaysOfTheWeek(ev, interval->days)) {
                        value->emplace_back(ev.first, ev.second);
                    }
                }
                return value;
            }
        }
        else if (e->isFunction) {
            auto value = std::make_unique<std::list<std::pair<EID, std::string>>>();
            std::string funcName = e->name;
            std::transform(funcName.begin(), funcName.end(), funcName.begin(), ::toupper);
            if (SUPPORTED_FUNCTIONS.count(funcName)) {
                if (e->isAliased) {
                    value->emplace_back(0, e->alias);
                    aliases[e->alias] = funcName;    // Uppercase transformation
                }
                else {
                    value->emplace_back(0, funcName);
                }

                if (funcName == "COUNT") {
                    auto results = executeExpressions(cid, e->nestedExpressions, conditions, groupBy, aliases);
                    value->emplace_back(0, std::to_string(results->size()));
                }
                else if (funcName == "WINDOW") {
                    if (e->nestedExpressions == nullptr || e->nestedExpressions->empty() ||
                        e->nestedExpressions->front()->type != hsql::kExprLiteralInterval) {
                        throw InvalidWindowArgumentException();
                    }

                    if (groupBy != nullptr && !groupBy->empty()) {
                        std::transform(groupBy->front()->name.begin(), groupBy->front()->name.end(),
                                       groupBy->front()->name.begin(), ::toupper);

                        if (groupBy->front()->name == "WINDOW") {
                            groupBy->front()->expression = SelectExpression::intervalExpression(
                                    e->nestedExpressions->front()->value, e->nestedExpressions->front()->dateTime);
                        }

                        if (expressions->size() > 1 && expressions->at(1)->isFunction) {
                            executeWindow(cid, conditions, groupBy, *value, expressions->at(1));
                        }
                        else {
                            executeWindow(cid, conditions, groupBy, *value, nullptr);
                        }

                    }
                }
                return value;
            }
            else {
                throw InvalidAggregationException();
            }
        }
        else {
            // Handle other expression types
        }
    }

    return nullptr; // Changed from {} to nullptr for clarity
}

long ChronoSQLParser::getIntervalSeconds(SelectExpression* interval) {
    return interval->value * intervalConversions[interval->dateTime];
}

void ChronoSQLParser::executeWindow(const CID& cid, const std::list<ConditionExpression*>* conditions,
                   std::list<GroupByExpression*>* groupBy, std::list<std::pair<EID, std::string>>& value,
                   SelectExpression* aggregate) {
    auto interval = extractInterval(conditions);
    auto events = getReplayDataFromWorker(cid, interval->startEID, interval->endEID);

    if (!events->empty()) {
        long intervalSize = getIntervalSeconds(groupBy->front()->expression);
        long currentAgg = 0;
        EID intervalStart = events->front().first;
        EID intervalEnd = intervalStart + intervalSize;

        for (const auto& ev : *events) {
            if (!eventMeetsDaysOfTheWeek(ev, interval->days)) {
                continue;
            }

            if (ev.first >= intervalEnd) {
                if (aggregate != nullptr) {
                    value.emplace_back(intervalStart, std::to_string(currentAgg));
                    currentAgg = 0;
                }

                intervalStart = intervalEnd + static_cast<EID>(floor((ev.first - intervalEnd) / intervalSize)) * intervalSize;
                intervalEnd = intervalStart + intervalSize;
            }

            if (aggregate == nullptr) {
                value.emplace_back(intervalStart, ev.second);
            }
            else {
                currentAgg++;
            }
        }

        if (aggregate != nullptr) {
            value.emplace_back(intervalStart, std::to_string(currentAgg));
        }

    }

    // No manual deletion
}

bool
ChronoSQLParser::eventMeetsDaysOfTheWeek(std::pair<EID, std::string> ev, const std::list<Enumerations::DayOfTheWeek>& dows) {
    if (dows.empty()) {
        return true;
    }

    for (Enumerations::DayOfTheWeek dow : dows) {
        if (extractDayOfTheWeek(ev.first) == dow) {
            return true;
        }
    }
    return false;
}

Enumerations::DayOfTheWeek ChronoSQLParser::extractDayOfTheWeek(EID eid) {
    // Assumption: day of the week is in UTC
    // January 1, 1970, 00.00 was Thursday, 86400 seconds in a day
    int dow = (static_cast<long>(floor(eid / 86400)) + 4) % 7;
    return static_cast<Enumerations::DayOfTheWeek>(dow);
}

void ChronoSQLParser::printException(std::exception& e) {
    std::cout << e.what() << std::endl;
}

std::string ChronoSQLParser::longToChar(long value) {
    return std::to_string(value);
}

std::unique_ptr<std::list<std::pair<EID, std::string>>> ChronoSQLParser::executeJoin(const hsql::JoinDefinition* joinDef, const std::list<ConditionExpression*>* conditions) {
    auto interval_ptr = this->extractInterval(conditions);

    auto leftEvents = this->getReplayDataFromWorker(joinDef->left->getName(), interval_ptr->startEID, interval_ptr->endEID);
    auto rightEvents = this->getReplayDataFromWorker(joinDef->right->getName(), interval_ptr->startEID, interval_ptr->endEID);

    auto joinResults = std::make_unique<std::list<std::pair<EID, std::string>>>();

    if (joinDef->type == hsql::kJoinInner || joinDef->type == hsql::kJoinLeft) {
        for (const auto& leftEvent : *leftEvents) {
            bool matchFound = false;
            for (const auto& rightEvent : *rightEvents) {
                if (rightEvent.first > leftEvent.first) {
                    break;
                }
                if (evaluateJoinCondition(leftEvent, rightEvent, joinDef->condition)) {
                    std::string combinedPayload = leftEvent.second + " | " + rightEvent.second;
                    joinResults->emplace_back(leftEvent.first, combinedPayload);
                    matchFound = true;
                }
            }
            if (joinDef->type == hsql::kJoinLeft && !matchFound) {
                joinResults->emplace_back(leftEvent.first, leftEvent.second);
            }
        }
    }

    return joinResults;
}

bool ChronoSQLParser::evaluateJoinCondition(const std::pair<EID, std::string>& leftEvent, const std::pair<EID, std::string>& rightEvent, const hsql::Expr* condition) {
    if (condition->opType == hsql::kOpEquals) {
        return leftEvent.first == rightEvent.first;
    }
    return false;
}

int ChronoSQLParser::parseSelectStatement(const hsql::SelectStatement* statement, QueryResponse *response) {
    auto expressions = std::make_unique<std::vector<SelectExpression*>>();
    std::unordered_map<std::string, std::string> aliases;

    for (hsql::Expr* expr : *statement->selectList) {
        SelectExpression* e = parseSelectToken(expr, aliases);
        if (e == nullptr) {
            return -1;
        }

        expressions->push_back(e);
    }

    std::unique_ptr<std::list<ConditionExpression*>> conditions = nullptr;
    if (statement->whereClause != nullptr) {
        conditions = std::unique_ptr<std::list<ConditionExpression*>>(parseWhereExpression(statement->whereClause));
    }

    std::unique_ptr<std::list<GroupByExpression*>> groupByExpressions = nullptr;
    if (statement->groupBy != nullptr) {
        groupByExpressions = parseGroupBy(statement->groupBy, aliases);
    }

    const hsql::TableRef* fromTable = statement->fromTable;
    if (fromTable->type == hsql::kTableJoin) {
        const hsql::JoinDefinition* join = fromTable->join;

        try {
            auto joinResults = this->executeJoin(join, conditions.get());
            this->printResults(std::move(joinResults), aliases, std::move(groupByExpressions), response);
        } catch (const std::exception &e) {
            std::cout << "Error executing join: " + std::string(e.what()) << std::endl;
            return -1;
        }

        return 0;
    }

    std::unique_ptr<std::list<std::pair<EID, std::string>>> results;

    try {
        results = executeExpressions(statement->fromTable->name, expressions.get(), conditions.get(), groupByExpressions.get(), aliases);
    }
    catch (ChronicleNotFoundException& e) {
        std::cout << "ERROR: Chronicle \"" << statement->fromTable->name << "\" does not exist" << std::endl;
        return -1;
    }
    catch (FieldNotFoundException& e) {
        std::cout << "ERROR: Field \"" << e.getField() << "\" does not exist" << std::endl;
        return -1;
    }
    catch (InvalidWindowArgumentException& e) {
        printException(e);
        return -1;
    }
    catch (InvalidAggregationException& e) {
        printException(e);
        return -1;
    }
    catch (UnrecognizedDayOfTheWeek& e) {
        printException(e);
        return -1;
    }

    printResults(std::move(results), aliases, std::move(groupByExpressions), response);

    // No need to manually delete anything; unique_ptr will automatically handle memory
    return 0;
}
