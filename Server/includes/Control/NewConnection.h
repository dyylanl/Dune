#ifndef __NEW_CONNECTION_H__
#define __NEW_CONNECTION_H__
#include <utility>

#include "../../../Common/includes/Socket/Socket.h"


//-----------------------------------------------------------------------------
// Basicamente contiene el socket, proyecta a cargarle mas info a la nueva conexion...
struct NewConnection {

    Socket peer;
    std::string name;
    int house{};

    // ------------ Constructor ------------ //
    explicit NewConnection(Socket& peer) : peer(std::move(peer)) {}
    NewConnection(Socket& peer, std::string name1, int house1) : peer(std::move(peer)), name(std::move(name1)), house(house1){}
};

//-----------------------------------------------------------------------------

#endif  // __NEW_CONNECTION_H__
