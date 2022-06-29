//
// Created by riclui on 11/06/22.
//

#ifndef DUNE_RECVTHREAD_H
#define DUNE_RECVTHREAD_H


#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Object/GameObject.h"
#include "../Queue/NBQueue.h"

#define BARRACKS_KEY 'b'
#define CONSTRUCTION_CENTER_KEY 'c'
#define HEAVY_FACTORY_KEY 'h'
#define LIGHT_FACTORY_KEY 'l'
#define REFINERY_KEY 'r'
#define SILO_KEY 's'
#define WIND_TRAP_KEY 'w'
#define PALACE_KEY 'p'

enum Type{UNIT, BUILD, BUTTON};

class RecvThread : public Thread {
private:
    NBQueue<std::vector<std::unique_ptr<GameObject>>> &m_quene;
    Socket &m_socket;
    Protocol &m_protocol;
    std::atomic<bool> running;
public:
    RecvThread(NBQueue<std::vector<std::unique_ptr<GameObject>>> &quene, Socket &socket, Protocol &protocol)
            : m_quene(quene), m_socket(socket), m_protocol(protocol), running(true){}

    void run() override;

    void addVehicle(std::vector<std::unique_ptr<GameObject>> &gameObjects);

    void stop();

    void addBuild(std::vector<std::unique_ptr<GameObject>> &gameObjects);

    void addButtonBuild(std::vector<std::unique_ptr<GameObject>> &gameObjects);
};


#endif //DUNE_RECVTHREAD_H
