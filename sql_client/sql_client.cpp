#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <fstream>

// Include gRPC headers
#include <grpcpp/grpcpp.h>
#include "../proto/sql_service.grpc.pb.h"

// Include RapidJSON headers
#include "document.h"
#include "error/en.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using sqlservice::QueryRouter;
using sqlservice::QueryRequest;
using sqlservice::QueryResponse;

// Function to read server addresses from a JSON file
std::vector<std::string> ReadServerAddresses(const std::string& filename) {
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

    if (!doc.HasMember("query_router_servers") || !doc["query_router_servers"].IsArray()) {
        std::cerr << "Invalid server configuration format." << std::endl;
        return servers;
    }

    for (const auto& server : doc["query_router_servers"].GetArray()) {
        if (server.IsString()) {
            servers.emplace_back(server.GetString());
        } else {
            std::cerr << "Invalid server address format in configuration." << std::endl;
        }
    }

    return servers;
}

class SQLClient {
public:
    SQLClient(const std::vector<std::string>& server_addresses)
        : servers_(server_addresses),
          rng_(std::random_device{}()),
          dist_(0, servers_.size() - 1) {
        if (servers_.empty()) {
            throw std::runtime_error("No valid server addresses provided.");
        }
    }

    // Method to execute an SQL query using a randomly selected server
    std::string ExecuteQuery(const std::string& query) {
        int retries = servers_.size();  // Retry with other servers if one fails
        while (retries-- > 0) {
            // Select a random server
            int index = dist_(rng_);
            const std::string& server_address = servers_[index];

            // Establish a connection to the selected server
            auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
            auto stub = QueryRouter::NewStub(channel);

            // Prepare request
            QueryRequest request;
            request.set_query(query);

            // Prepare response and context
            QueryResponse response;
            ClientContext context;

            // Call gRPC method
            Status status = stub->ExecuteQuery(&context, request, &response);

            if (status.ok()) {
                std::cout << "Query executed on server: " << server_address << std::endl;
                return response.result();
            } else {
                std::cerr << "gRPC call failed on server " << server_address
                          << ": " << status.error_message() << std::endl;
                std::cerr << "Retrying with another server..." << std::endl;
            }
        }

        // All retries failed
        return "Error: All servers are unavailable.";
    }

private:
    std::vector<std::string> servers_;
    std::mt19937 rng_;
    std::uniform_int_distribution<std::mt19937::result_type> dist_;
};

// Helper function to parse command-line arguments (not needed for load balancing)
std::string get_argument(int argc, char** argv, const std::string& flag, const std::string& default_value) {
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == flag && i + 1 < argc) {
            return argv[i + 1];
        }
    }
    return default_value;
}

int main(int argc, char** argv) {
    // Optional: Allow specifying the configuration file via command-line
    std::string config_file = get_argument(argc, argv, "--config", "/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/config.json");

    // Read server addresses from the configuration file
    std::vector<std::string> server_addresses = ReadServerAddresses(config_file);
    if (server_addresses.empty()) {
        std::cerr << "No servers available. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Available servers:" << std::endl;
    for (const auto& server : server_addresses) {
        std::cout << " - " << server << std::endl;
    }

    // Create SQL client with the list of server addresses
    SQLClient client(server_addresses);

    // Loop for accepting user input
    std::string query;
    while (true) {
        std::cout << "csql> ";
        std::getline(std::cin, query);

        if (query.empty()) {
            continue;
        }

        if (query == "exit") {
            break;
        }

        // Execute query and print result
        std::string result = client.ExecuteQuery(query);
        std::cout << result << std::endl;
    }

    return 0;
}
