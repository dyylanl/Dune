#ifndef __NEW_CONNECTION_H__
#define __NEW_CONNECTION_H__
#include "../../../Common/includes/Socket/Socket.h"


//-----------------------------------------------------------------------------
// Basicamente contiene el socket, proyecta a cargarle mas info a la conexion...
struct NewConnection {
    Socket peer;
    NewConnection(Socket& peer) : peer(std::move(peer)) {}
};

//-----------------------------------------------------------------------------

#endif  // __NEW_CONNECTION_H__
