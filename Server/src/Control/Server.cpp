#include "../../includes/Control/Server.h"
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"


Server::Server(const std::string& port, const int max_clients_queued) {}

void Server::run() {
    Map map(10,10);
    AStar pathfinding(map);
    Unit unit(1,1,5);
    Position pos(5,5);
    pathfinding.makePath(unit,pos);
    std::string input;
    do {
        std::getline(std::cin, input);
    } while (input != "q");
}

Server::~Server() {}

//-----------------------------------------------------------------------------
