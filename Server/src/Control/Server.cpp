#include "../../includes/Control/Server.h"
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"


Server::Server() {}

void Server::run() {
    std::cout << "Comenzando la ejecucion del servidor..." << std::endl;
    Map map(10,10);
    map.putTerrain(Terrain(Position(9,9),'C'));
    map.putTerrain(Terrain(Position(5,0),'P'));
    map.putTerrain(Terrain(Position(5,1),'P'));
    map.putTerrain(Terrain(Position(5,2),'P'));
    map.putTerrain(Terrain(Position(5,3),'P'));
    map.putTerrain(Terrain(Position(5,4),'P'));
    map.putTerrain(Terrain(Position(5,5),'P'));
    map.putTerrain(Terrain(Position(5,6),'P'));
    map.putTerrain(Terrain(Position(5,7),'P'));
    map.putTerrain(Terrain(Position(5,8),'P'));
    map.showTerrain();
    AStar aStar(map);
    Unit unit(0,0);
    std::stack<Position> path = aStar.makePath(unit,Position(9,9));
    if (path.empty()) {
        std::cout << "No hay una ruta disponible para llegar a destino." << std::endl;
    }
    while (!path.empty()) {
        Position pos = path.top();
        map.putTerrain(Terrain(pos,'C'));
        path.pop();
    }
    map.showTerrain();
    std::cout << "Finalizando la ejecucion del servidor..." << std::endl;
}

Server::~Server() {}