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
#include "../Object/GameObject.h"

enum UnitType{INFANTERIA_LIGERA, INFANTERIA_PESADA, FREMEN, SARDAUKAR, TRIKE, TANQUE_SONICO, RAIDER, DESVIADOR, TANQUE, DEVASTADOR, COSECHADORA};

class RecvThread : public Thread {
private:
    NonBlockingQueue<std::vector<GameObject*>> &m_quene;
    Socket &m_socket;
    Protocol &m_protocol;
    std::atomic<bool> running;
public:
    RecvThread(NonBlockingQueue<std::vector<GameObject*>> &quene, Socket &socket, Protocol &protocol)
            : m_quene(quene), m_socket(socket), m_protocol(protocol), running(true){}

    void run() override;

    void stop();
};


#endif //DUNE_RECVTHREAD_H
