// worker_client/worker_client.cpp

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "worker_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using workerservice::WorkerService;
using workerservice::ReplayRequest;
using workerservice::ReplayResponse;
using workerservice::Event;

// WorkerClient class to interact with the Worker Server
class WorkerClient {
public:
    // Constructor: initializes the gRPC stub
    WorkerClient(std::shared_ptr<Channel> channel)
        : stub_(WorkerService::NewStub(channel)) {}

    // Method to send a ReplayEvents request
    void ReplayEvents(const std::string& cid, int64_t start_eid, int64_t end_eid) {
        // Prepare the request
        ReplayRequest request;
        request.set_cid(cid);
        request.set_start_eid(start_eid);
        request.set_end_eid(end_eid);

        // Prepare the response and context
        ReplayResponse response;
        ClientContext context;

        // Make the RPC call
        Status status = stub_->ReplayEvents(&context, request, &response);

        // Handle the response
        if (status.ok()) {
            std::cout << "Received " << response.events_size() << " events:" << std::endl;
            for (const auto& event : response.events()) {
                std::cout << event.eid() << " " << event.data() << std::endl;
            }
        } else {
            std::cerr << "gRPC call failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<WorkerService::Stub> stub_;
};

// Helper function to parse command-line arguments
struct ClientOptions {
    std::string host = "localhost";
    std::string port = "50080";
    std::string cid = "mem_10k";
    int64_t start_eid = 1628780806;
    int64_t end_eid = 1658105202;
};

ClientOptions parse_arguments(int argc, char** argv) {
    ClientOptions options;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) {
            options.host = argv[++i];
        } else if (arg == "--port" && i + 1 < argc) {
            options.port = argv[++i];
        } else if (arg == "--cid" && i + 1 < argc) {
            options.cid = argv[++i];
        } else if (arg == "--start_eid" && i + 1 < argc) {
            options.start_eid = std::stoll(argv[++i]);
        } else if (arg == "--end_eid" && i + 1 < argc) {
            options.end_eid = std::stoll(argv[++i]);
        } else {
            std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
            exit(1);
        }
    }
    return options;
}

int main(int argc, char** argv) {
    // Parse command-line arguments
    ClientOptions options = parse_arguments(argc, argv);

    std::string server_address = options.host + ":" + options.port;
    std::cout << "Connecting to Worker Server at " << server_address << std::endl;

    // Create a WorkerClient instance
    WorkerClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    // Send a ReplayEvents request
    client.ReplayEvents(options.cid, options.start_eid, options.end_eid);

    return 0;
}
