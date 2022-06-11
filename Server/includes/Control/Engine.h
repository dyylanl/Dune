#ifndef __ENGINE_H__
#define __ENGINE_H__

//-----------------------------------------------------------------------------
#include <cstdio>
#include <atomic>
#include <chrono>
#include <cmath>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Thread.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "../Model/Game.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "../defs.h"
#include "../paths.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "NewConnection.h"
#include "YAMLReader.h"
#include "../../../Common/includes/Protocol.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Engine : public Thread {
private:
    std::atomic_bool keep_executing;
    YAMLReader& reader;
    int rate;
    NonBlockingQueue<NewConnection*>& new_connections;
    Game game;
    Protocol protocol;

    //-------------------------------------------------------------------------
    // Métodos privados

    /* Elimina las conexiones que finalizaron del contenedor de clientes */
    void _processFinishedConnections();

    /* Procesa los comandos en la cola de comandos y los ejecuta */
    void _processCommands();

    /* Procesa las solicitudes de nuevas conexiones */
    void _processNewConnections();

    /*
     * Envia los broadcasts con los cambios que se produjeron en una
     * iteracion del loop
     */
    void _sendDifferentialBroadcasts();

    /* Vacía las colas sin procesarlas para salir ordenadamente
     *     void _freeQueues();

     * */

    /* Iteración del loop */
    void _loopIteration(int it);

    //-------------------------------------------------------------------------

public:
    Engine(YAMLReader& reader,
           NonBlockingQueue<NewConnection*>& new_connections);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;
    //-------------------------------------------------------------------------
    void run() override;
    void stop();
    //-------------------------------------------------------------------------
    /* Destructor */
    ~Engine();
};

//-----------------------------------------------------------------------------

#endif  // __ENGINE_H__
