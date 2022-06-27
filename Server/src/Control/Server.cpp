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

        // comandos para el administrador del sistema.
        if (input == "l") {
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

    }

    game.stop();

    accepter.stop();
    //engine.stop();

    accepter.join();
    //engine.join();


}

Server::~Server() {}