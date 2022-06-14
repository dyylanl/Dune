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
#include "NewConnection.h"
#include "../../../Common/includes/Protocol.h"
//-----------------------------------------------------------------------------


class Engine : public Thread {
private:
    std::atomic_bool keep_executing;
    YAMLReader& reader;
    Protocol protocol;
    int rate;
    NonBlockingQueue<NewConnection*>& new_connections;
    NonBlockingQueue<InstanceId*> finished_connections;
    Game game;

    void _processFinishedConnections();
    void _processCommands();
    void _processNewConnections();
    void _freeQueues();
    void _loopIteration(int it);
public:
    Engine(YAMLReader& reader,
           NonBlockingQueue<NewConnection*>& new_connections);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;
    void run() override;
    void stop();
    ~Engine() override;
};


#endif  // __ENGINE_H__
