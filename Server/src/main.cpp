#include <cstdio>
#include <exception>
#include <string>
#include "../includes/Control/Server.h"


int main(int argc, char* argv[]) {
    std::string config_path = "../config.yaml";
    std::string port = "8082";
    if (argc == 3) {
        std::string port = argv[1];
        config_path = argv[2];
    } else if (argc == 2) {
        fprintf(stderr, ">>> Cargando configuracion por default.\n");
        port = argv[1];
    } else {
        fprintf(stderr, ">>> Cargando configuracion por default.\n");
        fprintf(stderr, ">>> Escuchando en puerto 8082.\n");
    }
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
