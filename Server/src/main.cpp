#include <cstdio>
#include <exception>
#include <string>
#include "../includes/Control/Server.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./server <port> <config_path> \n");
        return 1;
    }
    std::string port = argv[1];
    std::string config_path = argv[2];
    try {
        Server server(config_path, port, MAX_CLIENTS_QUEUED);
        server.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
        return 1;
    }
    return 0;
}


