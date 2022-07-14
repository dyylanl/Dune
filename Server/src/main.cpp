#include <cstdio>
#include <exception>
#include <string>
#include "../includes/Control/Server.h"


int main(int argc, char* argv[]) {
    std::string config_path = "../config.yaml";
    if (argc == 2) {
        fprintf(stderr, "Usage: ./server <port> <config_path> \nCargando configuracion por default...\n");
    } else {
        config_path = argv[2];
    }
    std::string port = argv[1];
    try {
        Server server(config_path, port, MAX_CLIENTS_QUEUED);
        server.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "[MAIN]: %s\n", e.what());
        return 1;
    } catch (...) {
        fprintf(stderr, "Unknown error.\n");
        return 1;
    }
    return 0;
}
