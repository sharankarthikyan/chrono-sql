#include <grpcpp/grpcpp.h>
#include "worker_service.grpc.pb.h"
#include "ChronoLog.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using workerservice::WorkerQueryRequest;
using workerservice::WorkerQueryResponse;
using workerservice::JoinEventsRequest;
using workerservice::JoinEventsResponse;

class WorkerServiceImpl final : public workerservice::WorkerService::Service {
public:
    // Constructor to initialize ChronoLog
    explicit WorkerServiceImpl(ChronoLog log) : chronoLog(std::move(log)) {}

    Status GetReplayData(ServerContext* context, const WorkerQueryRequest* request,
                         WorkerQueryResponse* response) override {
        std::string cid = request->cid();
        int64_t startEID = request->start_eid();
        int64_t endEID = request->end_eid();

        std::cout << "Processing replay request: CID=" << cid
            << ", StartEID=" << startEID << ", EndEID=" << endEID << std::endl;

        // Simulating chronoLog->replay functionality
        auto events = chronoLog.replay(cid, startEID, endEID);

        for (const auto& event : *events) {
            workerservice::Event* e = response->add_events();
            e->set_eid(event.first);
            e->set_data(event.second);
        }

        return Status::OK;
    }

   Status JoinEvents(ServerContext* context, const JoinEventsRequest* request,
                     JoinEventsResponse* response) override {
        // Create a map for left events based on EID
        std::unordered_map<int64_t, std::string> left_map;
        for (const auto& event : request->left_events()) {
            left_map[event.eid()] = event.data();
        }

        // Create a map for right events based on EID
        std::unordered_map<int64_t, std::string> right_map;
        for (const auto& event : request->right_events()) {
            right_map[event.eid()] = event.data();
        }

        workerservice::JoinType join_type = request->join_type();

        if (join_type == workerservice::JoinType::INNER) {
            // Perform Inner Join
            for (const auto& [eid, left_data] : left_map) {
                auto it = right_map.find(eid);
                if (it != right_map.end()) {
                    // EID match found, combine data
                    std::string combined_data = left_data + " | " + it->second;
                    workerservice::Event* joined_event = response->add_joined_events();
                    joined_event->set_eid(eid);
                    joined_event->set_data(combined_data);
                }
            }
        }
        else if (join_type == workerservice::JoinType::LEFT) {
            // Perform Left Join
            for (const auto& [eid, left_data] : left_map) {
                auto it = right_map.find(eid);
                if (it != right_map.end()) {
                    // EID match found, combine data
                    std::string combined_data = left_data + " | " + it->second;
                    workerservice::Event* joined_event = response->add_joined_events();
                    joined_event->set_eid(eid);
                    joined_event->set_data(combined_data);
                }
                else {
                    // No match found, include left event data only
                    workerservice::Event* joined_event = response->add_joined_events();
                    joined_event->set_eid(eid);
                    joined_event->set_data(left_data + " | "); // Right data is empty
                }
            }
        }
        else {
            return Status(grpc::INVALID_ARGUMENT, "Unsupported join type.");
        }

        return Status::OK;
    }

private:
    ChronoLog chronoLog; // ChronoLog instance
};

void RunWorkerServer(const std::string& server_address) {

    ConfigurationManager configManager("/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/config.json");
    auto config = configManager.getConfiguration();

    ChronoLog log(config);

    WorkerServiceImpl service(log);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Worker server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    std::string host = "0.0.0.0";
    std::string port = "50052"; // Default port for worker

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) {
            host = argv[++i];
        }
        else if (arg == "--port" && i + 1 < argc) {
            port = argv[++i];
        }
    }

    std::string server_address = host + ":" + port;
    RunWorkerServer(server_address);

    return 0;
}
