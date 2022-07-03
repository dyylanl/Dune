#ifndef __CLIENT_LOGIN_H__
#define __CLIENT_LOGIN_H__

#include <cstdio>
#include <atomic>
#include <exception>
//-----------------------------------------------------------------------------
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../../Common/includes/Exceptions/LoginException.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/Thread.h"
//-----------------------------------------------------------------------------
#include "NewConnection.h"
#include "../Model/Game.h"
//-----------------------------------------------------------------------------

class ClientLogin : public Thread {
private:
    std::atomic_bool is_running;
    Socket peer;
    Protocol protocol;
    Game& game;

    /* ejecuta el comando recibido.
    *   1: crear partida
    *   2: unirse a partida
    *   3: listar partidas
    * 
    * retorna 0 si el jugador ya se unio a una partida (o creo).
    * retorna 1 si el jugador decidio listar las partidas, por lo que no se unio a niguna.
    */
    void execute(uint8_t command, std::string name_player);

public:
    ClientLogin(Game& game, Socket& peer);
    ClientLogin(const ClientLogin&) = delete;
    ClientLogin& operator=(const ClientLogin&) = delete;
    ClientLogin(ClientLogin&& other) = delete;
    ClientLogin& operator=(ClientLogin&& other) = delete;

    /*
     * Luego de haber aceptado una conexion, el servidor requiere los datos del nuevo cliente.
     */
    void run() override;
    bool isRunning() const;
    void stop();

    ~ClientLogin() override;
};


#endif  // __CLIENT_LOGIN_H__
