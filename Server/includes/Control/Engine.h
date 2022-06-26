#ifndef __ENGINE_H__
#define __ENGINE_H__


#include <cstdio>
#include <atomic>
#include <chrono>
#include <cmath>
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Thread.h"
#include "NewConnection.h"
#include "Commands/Command.h"
#include "ClientsConnected.h"


class Engine : public Thread {
private:

    std::atomic_bool keep_executing;
    int rate;

    NonBlockingQueue<NewConnection*>& new_connections;
    NonBlockingQueue<InstanceId*> finished_connections;

    // comandos que recibe de los clientes
    NonBlockingQueue<Command*> commands;
    // la que envia el server
    NonBlockingQueue<Command*> snapshot;

    // todos los clientes del mapa
    ClientsConnected established_connections;

    void _processFinishedConnections();
    void _processCommands();
    void _freeQueues();
    void _loopIteration(int it);
public:
    Engine(Map *map, NonBlockingQueue<NewConnection*>& new_connections);
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;
    void run() override;
    void stop();
    ~Engine() override;
    void addClient(NewConnection* client);
};


#endif  // __ENGINE_H__
