#include <cstdio>
#include <exception>
#include <string>
#define MAX_CLIENTS_QUEUED 10
// ----------------------------------------------------------------------------
#include "../includes/Control/Server.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./server <port>\n");
        return 1;
    }

    std::string port = argv[1];

    try {
        Server server(port, MAX_CLIENTS_QUEUED);
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

// ----------------------------------------------------------------------------
