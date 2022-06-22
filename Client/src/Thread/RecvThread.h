//
// Created by riclui on 11/06/22.
//

#ifndef DUNE_RECVTHREAD_H
#define DUNE_RECVTHREAD_H


#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Object/GameObject.h"

enum VehicleType {TRIKE, SONIC_TANK, RAIDER, DESVIATOR, TANK, DEVASTATOR, HARVESTER};
enum BuilType {CONSTRUCTION_YARD};

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
