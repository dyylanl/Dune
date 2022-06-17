//
// Created by riclui on 16/06/22.
//

#ifndef DUNE_SENDTHREAD_H
#define DUNE_SENDTHREAD_H


#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/BlockingQueue.h"
#include "../../../Common/includes/Socket/Socket.h"
#include "../../../Common/includes/Protocol.h"
#include "Action.h"

class SendThread : public Thread{
private:
    BlockingQueue<Action*> &m_quene;
    Socket &m_socket;
    Protocol &m_protocol;
    std::atomic<bool> running;
public:
    SendThread(BlockingQueue<Action*> &quene, Socket &socket, Protocol &protocol)
            : m_quene(quene), m_socket(socket), m_protocol(protocol), running(true){}

    void run() override;

    void stop();

    void actionProcess(const Action *action);
};


#endif //DUNE_SENDTHREAD_H
