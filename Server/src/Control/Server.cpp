#include "../../includes/Control/Server.h"


void Server::printGames() {
    std::cout << "Partidas: " << std::endl;
    std::vector<std::vector<std::string>> list = game.listGames();
    if (!list.empty()) {
        int n = (int)list.size();
        for (int i = 0; i < n; i++) {
            std::cout << list[i][2] << " " << list[i][0] << "/" << list[i][1] << std::endl;
        }
    } else {
        std::cout << "No hay partidas creadas..." << std::endl;
    }
}

void Server::printUploadedMaps() {
    std::cout << "Mapas cargados: " << std::endl;
    std::vector<MapDTO> maps = game.getMapsLoads();
    int total = (int)maps.size();
    for (int i = 0; i < total; i++) {
        std::cout << "Id: " << maps[i].map_id << "\n Max players: " << maps[i].max_players << "\nRuta: " << maps[i].path << std::endl;
    }
}


Server::Server(const std::string& config_path, const std::string& port, const int max_clients_queued) :
          game(config_path),
          accepter(game, port, max_clients_queued) 
          {}

void Server::run() {

    // Se lanza el hilo aceptador de conexiones.
    accepter.start();

    /*
     * Comandos
     */
    std::string input;
    while (input != "q") {
        std::cin >> input;

        
        if (input == "l") {
            printGames();
        }

        if (input == "m") {
            printUploadedMaps();
        }

        if (input == "c") {
            system("clear");
        }

    }

    game.stop();

    accepter.stop();
    accepter.join();


}

Server::~Server() {}