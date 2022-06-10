#include <utility>
#include "../../includes/Control/Server.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../includes/Model/Position.h"
#include "../../includes/Model/Terrains/Terrain.h"
#include "../../includes/Model/Map.h"
#include "../../includes/Model/AStar.h"
#include <arpa/inet.h>


Server::Server(std::string port1, int max_clients_queued1) : port(std::move(port1)), max_clients_queued(max_clients_queued1) {}

void Server::run() {
    std::cout << "Comenzando la ejecucion del servidor..." << std::endl;
    Socket socket(port,max_clients_queued);
    auto peer = socket.accept();


    /*uint16_t msj;
    int cant_bytes;
    cant_bytes = peer.recv((char*)&msj, sizeof(uint16_t));
    std::cout << cant_bytes << std::endl;
    std::cout << "Se recibio: " << msj << std::endl;*/



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
    map.putTerrain(Terrain(Position(-2,25),'P'));
    map.showTerrain();
    AStar aStar(map);
    Unit unit(2,2);
/********************************
 * Se envia posicion inicial
 ********************************/
    uint16_t posX = unit.getPosition().x;
    uint16_t posY = unit.getPosition().y;
    peer.send((char*)&posX, sizeof(uint16_t));
    peer.send((char*)&posY, sizeof(uint16_t));
/****
 * Recibo posicion de destino
 ****/
    peer.recv((char*)&posX, sizeof(uint16_t));
    peer.recv((char*)&posY, sizeof(uint16_t));

    std::cout << posX << "," << posY << std::endl;

    std::stack<Position> path = aStar.makePath(unit,Position(posX,posY));
    if (path.empty()) {
        std::cout << "No hay una ruta disponible para llegar a destino." << std::endl;
    }

    /* Se envia el tamanio*/
    uint16_t size = path.size();
    peer.send((char*)&size, sizeof(uint16_t));

    uint16_t posX1;
    uint16_t posY1;

    while (!path.empty()) {
        Position pos = path.top();
        posX1 = pos.x;
        posY1 = pos.y;
        peer.send((char*)&posX1, sizeof(uint16_t));
        peer.send((char*)&posY1, sizeof(uint16_t));
        path.pop();
    }


    /*while (!path.empty()) {
        Position pos = path.top();
        map.putTerrain(Terrain(pos,'C'));
        path.pop();
    }
    map.showTerrain();*/
    std::cout << "Finalizando la ejecucion del servidor..." << std::endl;
}

Server::~Server() {}