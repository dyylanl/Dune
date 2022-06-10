#include "../../includes/Control/Server.h"


Server::Server(const std::string& path) : reader(path), accepter(reader.getPort()) {}

void Server::run() {
    std::cout << "Comenzando la ejecucion del servidor..." << std::endl;

    accepter.start(); // Se lanza el hilo aceptador de conexiones.

    std::string input;
    while (input != "q") {
        std::cin >> input;
    }

    accepter.stop();
    accepter.join();

    std::cout << "Finalizando la ejecucion del servidor..." << std::endl;
}

Server::~Server() {}