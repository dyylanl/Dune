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
    YAMLReader& reader;
    NonBlockingQueue<NewConnection*>& new_connections;
    Game& game;

public:
    ClientLogin(Game& game,Socket& peer, YAMLReader& reader,
                NonBlockingQueue<NewConnection*>& new_connections);
    ClientLogin(const ClientLogin&) = delete;
    ClientLogin& operator=(const ClientLogin&) = delete;
    ClientLogin(ClientLogin&& other) = delete;
    ClientLogin& operator=(ClientLogin&& other) = delete;

    /*
     * Utilizada para la carga de configuracion del nuevo cliente.
     */
    void run() override;
    int execute(uint16_t command, std::string name_player);
    bool isRunning() const;
    void stop();

    ~ClientLogin() override;
};


#endif  // __CLIENT_LOGIN_H__
