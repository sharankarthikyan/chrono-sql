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

std::list<std::pair<int64_t, std::string>> WorkerClient::joinEvents(
    const std::list<std::pair<int64_t, std::string>>& leftEvents,
    const std::list<std::pair<int64_t, std::string>>& rightEvents,
    workerservice::JoinType joinType) {

    workerservice::JoinEventsRequest request;
    for (const auto& event : leftEvents) {
        workerservice::Event* e = request.add_left_events();
        e->set_eid(event.first);
        e->set_data(event.second);
    }
    for (const auto& event : rightEvents) {
        workerservice::Event* e = request.add_right_events();
        e->set_eid(event.first);
        e->set_data(event.second);
    }
    request.set_join_type(joinType);

    workerservice::JoinEventsResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->JoinEvents(&context, request, &response);

    if (!status.ok()) {
        throw std::runtime_error("JoinEvents RPC failed: " + status.error_message());
    }

    std::list<std::pair<int64_t, std::string>> joinedEvents;
    for (const auto& event : response.joined_events()) {
        joinedEvents.emplace_back(event.eid(), event.data());
    }

    return joinedEvents;
}