#ifndef __NEW_CONNECTION_H__
#define __NEW_CONNECTION_H__
#include <utility>

#include "../../../Common/includes/Socket/Socket.h"
#include "../defs.h"


/*
*   Contiene la informacion de una nueva conexion
    * Nombre
    * Mapa en el que jugara
    * Id de conexion
    * Socket para el envio/recibo de paquetes
*/
struct NewConnection {
    Socket peer;
    std::string name_player;
    std::string name_game;
    int house;
    NewConnection(Socket& peer, std::string name_player1, std::string name_game1) :
                    peer(std::move(peer)),
                    name_player(std::move(name_player1)),
                    name_game(std::move(name_game1)),
                    house(0) {}
};

#endif  // __NEW_CONNECTION_H__
