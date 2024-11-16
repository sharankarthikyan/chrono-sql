#include "WorkerClient.h"

// Constructor implementation
WorkerClient::WorkerClient(std::shared_ptr<grpc::Channel> channel)
    : stub_(workerservice::WorkerService::NewStub(channel)) {}

// Fetch replay data from worker server
std::list<std::pair<int64_t, std::string>> WorkerClient::getReplayData(const std::string& cid, int64_t startEID, int64_t endEID) {
    workerservice::WorkerQueryRequest request;
    request.set_cid(cid);
    request.set_start_eid(startEID);
    request.set_end_eid(endEID);

    workerservice::WorkerQueryResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetReplayData(&context, request, &response);

    if (!status.ok()) {
        throw std::runtime_error("Failed to get replay data: " + status.error_message());
    }

    std::list<std::pair<int64_t, std::string>> results;
    for (const auto& event : response.events()) {
        results.emplace_back(event.eid(), event.data());
    }

    return results;
}
