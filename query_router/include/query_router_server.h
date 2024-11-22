#ifndef QUERY_ROUTER_SERVER_H
#define QUERY_ROUTER_SERVER_H

#include <grpcpp/grpcpp.h>
#include "../proto/sql_service.grpc.pb.h"


#include <cassert>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "ChronoSQLParser.h"
#include "ConfigurationManager.h"
#include "ConfigurationValues.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using sqlservice::QueryRouter;
using sqlservice::QueryRequest;
using sqlservice::QueryResponse;

class QueryRouterAsyncServer {
public:
    explicit QueryRouterAsyncServer(const std::string& server_address, const std::string& config_path)
        : server_address_(server_address), config_path_(config_path), service_(), cq_(), is_shutdown_(false) {}

    ~QueryRouterAsyncServer() {
        Shutdown();
    }

    void Run() {
        ServerBuilder builder;
        builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);

        cq_ = builder.AddCompletionQueue();
        server_ = builder.BuildAndStart();
        std::cout << "Asynchronous Query Router Server listening on " << server_address_ << std::endl;

        HandleRpcs();

        server_->Wait();
    }

    void Shutdown() {
        if (!is_shutdown_) {
            is_shutdown_ = true;
            server_->Shutdown();
            cq_->Shutdown();
        }
    }

private:
    class CallData {
    public:
        QueryRouter::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext context_;

        QueryRequest request_;

        QueryResponse response_;

        grpc::ServerAsyncResponseWriter<QueryResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;

        std::shared_mutex& mutex_;
        std::string config_path_;

        CallData(QueryRouter::AsyncService* service, ServerCompletionQueue* cq, std::shared_mutex& mutex, const std::string& config_path)
            : service_(service), cq_(cq), responder_(&context_), status_(CREATE), mutex_(mutex), config_path_(config_path) {
            Proceed();
        }

        void Proceed() {
            if (status_ == CREATE) {
                // As part of the initial CREATE state, we request that the system start processing ExecuteQuery requests.
                status_ = PROCESS;
                service_->RequestExecuteQuery(&context_, &request_, &responder_, cq_, cq_, this);
            }
            else if (status_ == PROCESS) {
                // Spawn a new CallData instance to serve new clients while we process this one.
                new CallData(service_, cq_, mutex_, config_path_);

                // The actual processing.
                std::unique_lock<std::shared_mutex> lock(mutex_);

                std::string query = request_.query();
                std::cout << "Received query: " << query << std::endl;

                ConfigurationManager configManager(config_path_);
                auto config = configManager.getConfiguration();

                auto parser = std::make_unique<ChronoSQLParser>(config, config_path_);

                if (query.empty()) {
                    response_.set_result("Error: Received an empty query.");
                }
                else {
                    std::cout << "Parsing query: " << query << std::endl;
                    parser->parse(query, &response_);
                }

                status_ = FINISH;
                responder_.Finish(response_, Status::OK, this);
            }
            else {
                assert(status_ == FINISH);
                delete this;
            }
        }
    };

    void HandleRpcs() {
        new CallData(&service_, cq_.get(), mutex_, config_path_);

        void* tag;
        bool ok;
        while (cq_->Next(&tag, &ok)) {
            if (ok) {
                static_cast<CallData*>(tag)->Proceed();
            }
            else {
                // Handle the case where the RPC was not successful.
                std::cerr << "RPC failed: Tag not ok." << std::endl;
                delete static_cast<CallData*>(tag);
            }
        }
    }

    std::string server_address_;
    std::string config_path_;
    QueryRouter::AsyncService service_;
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<Server> server_;
    std::shared_mutex mutex_;
    bool is_shutdown_;
};

#endif // QUERY_ROUTER_SERVER_H
