#include "../../includes/Control/Server.h"

//-----------------------------------------------------------------------------
// Métodos privados

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

Server::Server(const std::string& port, const int max_clients_queued) :
          accepter(port, max_clients_queued) {}

void Server::run() {
    accepter.start();
    std::string input;
    do {
        std::getline(std::cin, input);
    } while (input != "q");
    accepter.stop();
    accepter.join();
    fprintf(stderr, "DEBUG: Accepter joineado.\n");
}

Server::~Server() {}

//-----------------------------------------------------------------------------
