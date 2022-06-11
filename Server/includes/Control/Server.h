#ifndef __SERVER_H__
#define __SERVER_H__

//-----------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "Accepter.h"
#include "NewConnection.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "../../../Common/includes/NonBlockingQueue.h"
#include "YAMLReader.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Server {
private:
    YAMLReader reader;
    NonBlockingQueue<NewConnection*> new_connections;
    Accepter accepter;
    //Engine engine;

    //-------------------------------------------------------------------------
    // Métodos privados
    //-------------------------------------------------------------------------

public:
    /* Constructor */
    Server(const std::string& port, const int max_clients_queued);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void run();
    ~Server();
};

//-----------------------------------------------------------------------------

#endif  // __SERVER_H__
