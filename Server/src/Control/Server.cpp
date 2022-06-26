#include "../../includes/Control/Server.h"


Server::Server(const std::string& config_path, const std::string& port, const int max_clients_queued) :
          game(config_path),
          accepter(game, port, max_clients_queued) 
          {}

void Server::run() {
    // Se lanza el hilo aceptador de conexiones.
    accepter.start();

    // Se lanza el hilo motor del juego
    //engine.start();
    /*
     * Presionando la tecla 'q' por stdin cerramos el servidor.
     */
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }

    accepter.stop();
    //engine.stop();

    accepter.join();
    //engine.join();

}

Server::~Server() {}