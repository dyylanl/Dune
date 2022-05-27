#include "../../includes/Control/Server.h"


Server::Server(const std::string& port, const int max_clients_queued) {}

void Server::run() {

    // CREO MAPA Y CARGO ALGUNAS POSICIONES BLOQUEADAS.
    Map map(11,11);
    map.setValue(7,7,'B');
    map.setValue(7,8,'B');
    map.setValue(8,8,'B');
    map.setValue(8,7,'B');
    map.setValue(7,6,'B');
    map.showMap();

    // INICIALIZO EL ALGORITMO DE BUSQUEDA CON EL MAPA CARGADO.
    AStar aStar(map);

    // CREO LA UNIDAD EN (4,4) QUE SE MOVERA POR EL MAPA HASTA POS_END
    Unit unit(4,4,1);

    // POSICION DESTINO
    Position pos_end(10,10);

    // MEJOR RUTA ENCONTRADA POR EL ALGORITMO
    std::stack<Position> path = aStar.makePath(unit,pos_end);

    while (!path.empty()) {
        Position pos1 = path.top();
        map.setValue(pos1.getX(), pos1.getY(), 'P');
        path.pop();
    }
    map.showMap();
}

Server::~Server() {}

//-----------------------------------------------------------------------------
