#include "../../includes/Control/Server.h"
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"


Server::Server() {}

void Server::run() {

    std::cout << "Comenzando la ejecucion del servidor..." << std::endl;
    Map map(15,15);
    Position end(14,14);
    map.put(Position(0,5), "P");
    map.put(Position(1,5), "P");
    map.put(Position(2,5), "P");
    map.put(Position(3,5), "P");
    map.put(Position(4,5), "P");
    map.put(Position(5,5), "P");
    map.put(Position(6,5), "P");
    map.put(Position(7,5), "P");
    map.put(Position(8,5), "P");
    map.showMap();
    AStar astar(map);
    Unit unit(5,1);
    std::stack<Position> path = astar.makePath(unit,end);
    while (!path.empty()) {
        Position pos = path.top();
        map.put(pos,"C");
        path.pop();
    }
    map.showMap();
    std::cout << "Finalizando la ejecucion del servidor..." << std::endl;
}

Server::~Server() {}