#include "../../includes/Control/Server.h"


Server::Server(const std::string& config_path, const int max_clients_queued)
        : reader(config_path),
          new_connections(),
          accepter(reader.getPort(), max_clients_queued, reader, new_connections)
          /*,
          engine(reader, new_connections)*/ {}

void Server::run() {
    // Se lanza el hilo aceptador de conexiones.
    accepter.start();
    // Se lanza el hilo engine
    //engine.start();
    /*
     * Presionando la tecla 'q' por stdin cerramos el servidor.
     */
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
    accepter.stop();
    accepter.join();
/*
    engine.stop();
    engine.join();
*/
}

Server::~Server() {}