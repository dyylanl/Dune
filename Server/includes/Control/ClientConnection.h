#ifndef __CLIENT_CONNECTION_H__
#define __CLIENT_CONNECTION_H__

#include <atomic>
#include <exception>
#include <mutex>
#include <thread>
#include <iostream>
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Server/includes/defs.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Server/includes/Control/Commands/Command.h"
#include "Responses/Response.h"
#include "../Model/DTOs/snapshot.h"

class ClientConnection {
   private:
    InstanceId id;
    Socket peer;
    NonBlockingQueue<InstanceId*>& finished_connections;

    std::mutex m;
    int finished_threads;

    std::thread sender;
    BlockingQueue<Snapshot *> snapshots;

    std::thread receiver;
    NonBlockingQueue<Command*>& commands;

    Protocol protocol;

    void _finishThread();
    void _freeNotifications();
    void _sender();
    void _receiver();
    void _receiveCommand(uint8_t opcode);


   public:
    /* Constructor */
    ClientConnection(const InstanceId id,
                     Socket peer,
                     NonBlockingQueue<InstanceId*>& finished_connections,
                     NonBlockingQueue<Command*>& commands);

    ClientConnection(const ClientConnection&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;
    ClientConnection(ClientConnection&& other) = delete;
    ClientConnection& operator=(ClientConnection&& other) = delete;
    void start();


    void push(std::vector<BuildingDTO*> buildings, std::vector<UnitDTO*> units, std::vector<PlayerDTO*> players);


    void join();
    void stop();
    ~ClientConnection();
    void sendInitGame(std::vector<std::vector<char>>& map);
    InstanceId getId() {return id;}
    void sendEstablishConnection();
};


#endif  // __CLIENT_CONNECTION_H__
