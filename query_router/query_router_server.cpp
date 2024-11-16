#include <grpcpp/grpcpp.h>
#include "../proto/sql_service.grpc.pb.h"

#include <iostream>
#include <string>
#include <shared_mutex>
#include "ChronoSQLParser.h"
#include "ConfigurationManager.h"
#include "ConfigurationValues.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using sqlservice::QueryRouter;
using sqlservice::QueryRequest;
using sqlservice::QueryResponse;

class QueryRouterServiceImpl final : public QueryRouter::Service {
public:
    std::shared_mutex mutex_;

    Status HandleQuery(const QueryRequest* request, QueryResponse* response) {
        std::unique_lock<std::shared_mutex> lock(mutex_);

        std::string query = request->query();
        std::cout << "Received query: " << query << std::endl;
        
        ConfigurationManager configManager("/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/config.json");
        auto config = configManager.getConfiguration();

        auto parser = std::make_unique<ChronoSQLParser>(config, "/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/config.json");
        
        if (query.empty()) {
            response->set_result("Error: Received an empty query.");
            return Status::OK;
        }

        std::cout << "Parsing query: " << query << std::endl;
        parser->parse(query, response);

        return Status::OK;
    }

    Status ExecuteQuery(ServerContext* context, const QueryRequest* request,
                       QueryResponse* response) override {
        return HandleQuery(request, response);
    }
};

void RunServer(const std::string& server_address) {
    QueryRouterServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    std::string host = "0.0.0.0";
    std::string port = "50051";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) {
            host = argv[++i];
        } else if (arg == "--port" && i + 1 < argc) {
            port = argv[++i];
        }
    }

    std::string server_address = host + ":" + port;
    RunServer(server_address);

    return 0;
}
