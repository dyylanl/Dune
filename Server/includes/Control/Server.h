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
#include "Engine.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Server {
private:
    ConfigurationReader reader;
    Game game;
    NonBlockingQueue<NewConnection*> new_connections;
    Accepter accepter;
    Engine engine;

public:
    /* Constructor */
    Server(const std::string& port, int max_clients_queued);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;

    void run();
    ~Server();
};

//-----------------------------------------------------------------------------

#endif  // __SERVER_H__
