#ifndef WORKER_CLIENT_H
#define WORKER_CLIENT_H

#include <grpcpp/grpcpp.h>
#include "worker_service.grpc.pb.h"
#include <list>
#include <string>
#include <memory>
#include <stdexcept>
#include <utility>

class WorkerClient {
public:
    explicit WorkerClient(std::shared_ptr<grpc::Channel> channel);

    std::list<std::pair<int64_t, std::string>> getReplayData(const std::string& cid, int64_t startEID, int64_t endEID);

    std::list<std::pair<int64_t, std::string>> joinEvents(
        const std::list<std::pair<int64_t, std::string>>& leftEvents,
        const std::list<std::pair<int64_t, std::string>>& rightEvents,
        workerservice::JoinType joinType);

private:
    std::unique_ptr<workerservice::WorkerService::Stub> stub_;
};

#endif // WORKER_CLIENT_H
