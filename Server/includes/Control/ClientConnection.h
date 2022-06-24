#ifndef __CLIENT_CONNECTION_H__
#define __CLIENT_CONNECTION_H__

//-----------------------------------------------------------------------------
#include <atomic>
#include <exception>
#include <mutex>
#include <thread>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/Exceptions/Exception.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../../../Common/includes/Socket/Socket.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include "Commands/Command.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class ClientConnection {
private:
    InstanceId id;
    std::atomic<Id> map;
    Socket peer;
    NonBlockingQueue<InstanceId*>& finished_connections;
    // Comparten el int finished_threads => necesito el mutex
    std::mutex m;
    int finished_threads;

    std::thread sender;
    BlockingQueue<Command*> notifications;

    std::thread receiver;
    NonBlockingQueue<Command*>& commands;

    //Game &game;

    void _finishThread();
    // POR NO USAR PTR INTELIGENTES
    void _freeNotifications();
    void _sender();
    void _receiver();
    void _receiveCommand();

public:
    /* Constructor */
    ClientConnection(const InstanceId id,
                     const Id map,
                     Socket& peer,
                     NonBlockingQueue<InstanceId*>& finished_connections,
                     NonBlockingQueue<Command*>& commands);

    ClientConnection(const ClientConnection&) = delete;
    ClientConnection& operator=(const ClientConnection&) = delete;
    ClientConnection(ClientConnection&& other) = delete;
    ClientConnection& operator=(ClientConnection&& other) = delete;

    void start();
    void push(Command* notification);
    void changeMap(Id map_id);
    void join();
    void stop();
    ~ClientConnection();
};


#endif  // __CLIENT_CONNECTION_H__
