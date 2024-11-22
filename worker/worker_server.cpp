#include "worker_server.h"

int main(int argc, char** argv) {
    std::string host = "0.0.0.0";
    std::string port = "50052";
    std::string config_path = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--host" && i + 1 < argc) {
            host = argv[++i];
        }
        else if (arg == "--port" && i + 1 < argc) {
            port = argv[++i];
        }
        else if (arg == "--config" && i + 1 < argc) {
            config_path = argv[++i];
        }
        else {
            std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
            return 1;
        }
    }

    if (config_path.empty()) {
        std::cerr << "Configuration file path must be provided using --config." << std::endl;
        return 1;
    }

    if (!std::filesystem::exists(config_path)) {
        std::cerr << "Configuration file does not exist: " << config_path << std::endl;
        return 1;
    }

    std::string server_address = host + ":" + port;
    WorkerServer server(server_address, config_path);
    server.Run();

    return 0;
}
