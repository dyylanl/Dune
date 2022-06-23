//
// Created by riclui on 11/06/22.
//

#ifndef DUNE_RECVTHREAD_H
#define DUNE_RECVTHREAD_H


#include "../../../Common/includes/Thread.h"
#include "../../../Common/includes/Protocol.h"
#include "../../../Common/includes/NonBlockingQueue.h"
#include "../Object/GameObject.h"

enum Type{VEHICLE, BUILD, BUTTON};
enum VehicleType {TRIKE, SONIC_TANK, RAIDER, DESVIATOR, TANK, DEVASTATOR, HARVESTER};
enum BuilType {CONSTRUCTION_YARD, LIGHT_FACTORY, HEAVY_FACTORY,WIND_TRAP, SPICE_REFINERY,
    SPICE_SILO, BARRACKS, PALACE};

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

    void addVehicle(std::vector<GameObject*> &gameObjects);

    void stop();

    void addBuild(std::vector<GameObject *> &gameObjects);

    void addButton(std::vector<GameObject *> &gameObjects);
};


#endif //DUNE_RECVTHREAD_H
