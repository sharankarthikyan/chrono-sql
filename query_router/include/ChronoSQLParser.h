#include "sql_service.grpc.pb.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <set>
#include "SQLParser.h"
#include "SelectExpression.h"
#include "ConditionExpression.h"
#include "GroupByExpression.h"
#include "EventInterval.h"
#include "FieldNotFoundException.h"
#include "InvalidWindowArgumentException.h"
#include "InvalidAggregationException.h"
#include "UnrecognizedDayOfTheWeek.h"
#include "ConfigurationValues.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using sqlservice::QueryResponse;

#ifndef CHRONOSQL_SQLPARSER_H
#define CHRONOSQL_SQLPARSER_H

class ChronoSQLParser {
public:
    ChronoSQLParser(ConfigurationValues *config, const std::string& filename);
    void parse(const std::string& query, QueryResponse* response);

private:
    static std::unordered_map<hsql::DatetimeField, long> intervalConversions;
    static std::unordered_map<std::string, Enumerations::DayOfTheWeek> daysOfTheWeek;

    const std::set<std::string> SUPPORTED_FUNCTIONS = {"COUNT", "WINDOW"};

    void printResults(std::list<std::pair<EID, const char*>>* events,
                      std::unordered_map<std::string, std::string> aliases,
                      std::list<GroupByExpression*>* groupBy,
                      QueryResponse* response);

    std::vector<std::string> ReadServerAddresses(const std::string& filename);

    std::list<std::pair<EID, const char*>>* getReplayDataFromWorker(const std::string& cid, int64_t startEID, int64_t endEID);

    int parseSelectStatement(const hsql::SelectStatement* statement, QueryResponse* response);

    std::list<std::pair<EID, const char*>>*
    executeExpressions(const CID& cid, std::vector<SelectExpression*>* expressions,
                       const std::list<ConditionExpression*>* conditions,
                       std::list<GroupByExpression*>& groupBy,
                       std::unordered_map<std::string, std::string>& aliases);

    static EventInterval* extractInterval(const std::list<ConditionExpression*>* conditions);

    static long getIntervalSeconds(SelectExpression* interval);

    void executeWindow(const CID& cid, const std::list<ConditionExpression*>* conditions,
                       std::list<GroupByExpression*>& groupBy,
                       std::list<std::pair<EID, const char*>>& value,
                       SelectExpression* aggregate);

    static bool eventMeetsDaysOfTheWeek(std::pair<EID, const char*> ev, 
                                        const std::list<Enumerations::DayOfTheWeek>& dows);

    static Enumerations::DayOfTheWeek extractDayOfTheWeek(EID eid);

    std::list<ConditionExpression*>* parseWhereExpression(const hsql::Expr* expression);

    SelectExpression* parseSelectToken(hsql::Expr* expr, std::unordered_map<std::string, std::string>& aliases);

    static std::list<GroupByExpression*>* parseGroupBy(hsql::GroupByDescription* groupBy,
                                                       std::unordered_map<std::string, std::string> aliases);

    static void printException(std::exception& e);

    static std::string longToChar(long value);
};

#endif // CHRONOSQL_SQLPARSER_H
