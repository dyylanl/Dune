#include <cstdio>
#include <exception>
#include <string>
#include "../includes/Control/Server.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server <config_path> \n");
        return 1;
    }

    std::string config_path = argv[1];

    try {
        Server server(config_path);
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


