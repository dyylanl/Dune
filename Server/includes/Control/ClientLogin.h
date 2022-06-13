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
#include "YAMLReader.h"

//-----------------------------------------------------------------------------

class ClientLogin : public Thread {
private:
    std::atomic_bool is_running;
    Socket peer;
    YAMLReader& reader;
    NonBlockingQueue<NewConnection*>& new_connections;

public:
    ClientLogin(Socket& peer, YAMLReader& reader,
                NonBlockingQueue<NewConnection*>& new_connections);
    ClientLogin(const ClientLogin&) = delete;
    ClientLogin& operator=(const ClientLogin&) = delete;
    ClientLogin(ClientLogin&& other) = delete;
    ClientLogin& operator=(ClientLogin&& other) = delete;

    /* Handler para el log-in de un cliente */
    void run() override;

    /* Chequea si el hilo se sigue ejecutando */
    bool isRunning() const;

    /* Termina la conexión de manera forzosa */
    void stop();

    ~ClientLogin();
};


#endif  // __CLIENT_LOGIN_H__
