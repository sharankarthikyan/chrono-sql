#ifndef WORKER_SERVER_H
#define WORKER_SERVER_H

#include <grpcpp/grpcpp.h>
#include "worker_service.grpc.pb.h"
#include "ChronoLog.h"
#include "ConfigurationManager.h"
#include "ConfigurationValues.h"

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <filesystem>
#include <cassert>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using workerservice::WorkerService;
using workerservice::WorkerQueryRequest;
using workerservice::WorkerQueryResponse;
using workerservice::JoinEventsRequest;
using workerservice::JoinEventsResponse;
using workerservice::JoinType;

class WorkerServer {
public:
    WorkerServer(const std::string& server_address, const std::string& config_path)
    : server_address_(server_address),
      config_path_(config_path),
      service_(),
      cq_(),
      chronoLog_(ConfigurationManager(config_path_).getConfiguration()), // Initialize chronoLog_
      is_shutdown_(false) {
    
    }


    ~WorkerServer() {
        Shutdown();
    }

    void Run() {
        ServerBuilder builder;
        builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);

        cq_ = builder.AddCompletionQueue();
        server_ = builder.BuildAndStart();
        std::cout << "Asynchronous Worker Server listening on " << server_address_ << std::endl;

        // Spawn threads to handle RPCs
        HandleRpcs();

        // Wait for the server to shutdown
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
    // Base class for handling different RPCs
    class CallDataBase {
    public:
        virtual void Proceed() = 0;
        virtual ~CallDataBase() {}
    };

    // CallData for GetReplayData
    class GetReplayDataCallData : public CallDataBase {
    public:
        GetReplayDataCallData(WorkerService::AsyncService* service, ServerCompletionQueue* cq, ChronoLog& chronoLog)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), chronoLog_(chronoLog) {
            Proceed();
        }

        void Proceed() override {
            if (status_ == CREATE) {
                status_ = PROCESS;
                service_->RequestGetReplayData(&ctx_, &request_, &responder_, cq_, cq_, this);
            }
            else if (status_ == PROCESS) {
                // Spawn new CallData instance to serve new clients
                new GetReplayDataCallData(service_, cq_, chronoLog_);

                // Process the request
                std::cout << "Processing replay request: CID=" << request_.cid()
                          << ", StartEID=" << request_.start_eid()
                          << ", EndEID=" << request_.end_eid() << std::endl;

                auto events = chronoLog_.replay(request_.cid(), request_.start_eid(), request_.end_eid());

                for (const auto& event : *events) {
                    workerservice::Event* e = response_.add_events();
                    e->set_eid(event.first);
                    e->set_data(event.second);
                }

                status_ = FINISH;
                responder_.Finish(response_, Status::OK, this);
            }
            else {
                assert(status_ == FINISH);
                delete this;
            }
        }

    private:
        WorkerService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        WorkerQueryRequest request_;
        WorkerQueryResponse response_;

        grpc::ServerAsyncResponseWriter<WorkerQueryResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;

        ChronoLog& chronoLog_;
    };

    // CallData for JoinEvents
    class JoinEventsCallData : public CallDataBase {
    public:
        JoinEventsCallData(WorkerService::AsyncService* service, ServerCompletionQueue* cq, ChronoLog& chronoLog)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), chronoLog_(chronoLog) {
            Proceed();
        }

        void Proceed() override {
            if (status_ == CREATE) {
                status_ = PROCESS;
                service_->RequestJoinEvents(&ctx_, &request_, &responder_, cq_, cq_, this);
            }
            else if (status_ == PROCESS) {
                // Spawn new CallData instance to serve new clients
                new JoinEventsCallData(service_, cq_, chronoLog_);

                // Process the request
                std::unordered_map<int64_t, std::string> left_map;
                for (const auto& event : request_.left_events()) {
                    left_map[event.eid()] = event.data();
                }

                std::unordered_map<int64_t, std::string> right_map;
                for (const auto& event : request_.right_events()) {
                    right_map[event.eid()] = event.data();
                }

                JoinType join_type = request_.join_type();

                if (join_type == JoinType::INNER) {
                    for (const auto& [eid, left_data] : left_map) {
                        auto it = right_map.find(eid);
                        if (it != right_map.end()) {
                            std::string combined_data = left_data + " | " + it->second;
                            workerservice::Event* joined_event = response_.add_joined_events();
                            joined_event->set_eid(eid);
                            joined_event->set_data(combined_data);
                        }
                    }
                }
                else if (join_type == JoinType::LEFT) {
                    for (const auto& [eid, left_data] : left_map) {
                        auto it = right_map.find(eid);
                        if (it != right_map.end()) {
                            std::string combined_data = left_data + " | " + it->second;
                            workerservice::Event* joined_event = response_.add_joined_events();
                            joined_event->set_eid(eid);
                            joined_event->set_data(combined_data);
                        }
                        else {
                            workerservice::Event* joined_event = response_.add_joined_events();
                            joined_event->set_eid(eid);
                            joined_event->set_data(left_data + " | ");
                        }
                    }
                }
                else {
                    responder_.Finish(response_, Status(grpc::INVALID_ARGUMENT, "Unsupported join type."), this);
                    return;
                }

                status_ = FINISH;
                responder_.Finish(response_, Status::OK, this);
            }
            else {
                assert(status_ == FINISH);
                delete this;
            }
        }

    private:
        WorkerService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        JoinEventsRequest request_;
        JoinEventsResponse response_;

        grpc::ServerAsyncResponseWriter<JoinEventsResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;

        ChronoLog& chronoLog_;
    };

    void HandleRpcs() {
        // Spawn new CallData instances for each RPC type
        new GetReplayDataCallData(&service_, cq_.get(), chronoLog_);
        new JoinEventsCallData(&service_, cq_.get(), chronoLog_);

        void* tag;  // uniquely identifies a request.
        bool ok;
        while (cq_->Next(&tag, &ok)) {
            static_cast<CallDataBase*>(tag)->Proceed();
        }
    }

    std::string server_address_;
    std::string config_path_;
    WorkerService::AsyncService service_;
    std::unique_ptr<ServerCompletionQueue> cq_;
    std::unique_ptr<Server> server_;
    ChronoLog chronoLog_;
    bool is_shutdown_;
};

#endif // WORKER_SERVER_H
