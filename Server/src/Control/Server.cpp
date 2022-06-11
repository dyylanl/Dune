#include "../../includes/Control/Server.h"
#include "../../includes/defs.h"


Server::Server(const std::string& path) : reader(path), accepter(reader.getPort()) {}

void Server::run() {
    std::cout << "Comenzando la ejecucion del servidor..." << std::endl;
    reader.getBuild(PALACE);
    reader.getBuild(SILO);
    // Se lanza el hilo aceptador de conexiones.
    accepter.start();

    /*
     * Presionando la tecla 'q' por stdin cerramos el servidor.
     */
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }

    accepter.stop();
    accepter.join();

    std::cout << "Finalizando la ejecucion del servidor..." << std::endl;
}

Server::~Server() {}