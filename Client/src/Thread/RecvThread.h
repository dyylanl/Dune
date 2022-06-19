//
// Created by riclui on 11/06/22.
//

#ifndef DUNE_RECVTHREAD_H
#define DUNE_RECVTHREAD_H


#include "../../../Common/includes/Thread.h"
#include "../Characters/ObjectGame.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Characters/Object.h"

class RecvThread : public Thread {
private:
    NonBlockingQueue<Object*> &m_quene;
    Socket &m_socket;
    Protocol &m_protocol;
    std::atomic<bool> running;
public:
    RecvThread(NonBlockingQueue<Object*> &quene, Socket &socket, Protocol &protocol)
            : m_quene(quene), m_socket(socket), m_protocol(protocol), running(true){}

    void run() override;

    void stop();

    Object *
    createUnit(int objectType, int player, bool selectStatus, int posX, int posY, int posActX, int posActY, int life,
               bool action) const;
};


#endif //DUNE_RECVTHREAD_H
