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

class Command;

class ClientConnection {
private:
    InstanceId id;
    std::atomic<Id> map_id;
    Socket peer;
    NonBlockingQueue<InstanceId*>& finished_connections;
    // Comparten el int finished_threads => necesito el mutex
    std::mutex m;
    int finished_threads;
    std::thread sender;
    std::thread receiver;
    Protocol protocol;

    NonBlockingQueue<Command*>& commands;

    void _finishThread();
    // POR NO USAR PTR INTELIGENTES
    void _freeNotifications();
    void _sender();
    void _receiver();
    void _receiveCommand(uint8_t opcode);

public:
    /* Constructor */
    ClientConnection(const InstanceId id,
                     Socket& peer,
                     NonBlockingQueue<Command*>& commands,
                     NonBlockingQueue<InstanceId*>& finished_connections);

    ClientConnection(const ClientConnection&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;
    ClientConnection(ClientConnection&& other) = delete;
    ClientConnection& operator=(ClientConnection&& other) = delete;

    void start();
    void join();
    void stop();
    ~ClientConnection();


    void sendInitGame(std::vector<std::vector<char>>& map);
    void sendInitBuildings(std::vector<BuildingDTO> buildings);
    InstanceId getId(){return id;}
    
};


#endif  // __CLIENT_CONNECTION_H__
