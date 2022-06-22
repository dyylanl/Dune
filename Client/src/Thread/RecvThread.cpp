#include "RecvThread.h"
#include "../Characters/Vehicles/DeviatorCL.h"
#include "../Characters/Vehicles/TrikeCL.h"
#include "../Characters/Vehicles/SonicTankCL.h"
#include "../Characters/Vehicles/TankCL.h"
#include "../Characters/Vehicles/DevastatorCL.h"
#include "../Characters/Vehicles/HarvesterCL.h"

void RecvThread::run() {
    while (running) {
        int type;
        int objectType;
        int id;
        int player;
        bool selectStatus;
        int posX;
        int posY;
        int posActX;
        int posActY;
        int life;
        bool action;
        int size;

        std::vector<GameObject*> gameObjects;

        m_protocol.recvCountObject(m_socket, size);
        for (int i = 0; i < size; ++i) {
            m_protocol.recvType(m_socket, type);
            if (type == 1) {
                m_protocol.recvObjectType(m_socket, objectType);
                switch (objectType) {
                    case TRIKE:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new TrikeCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case SONIC_TANK:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new SonicTankCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case RAIDER:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new TrikeCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case DESVIATOR:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new DeviatorCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case TANK:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new TankCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case DEVASTATOR:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new DevastatorCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case HARVESTER:
                        m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                            posActY, life, action);
                        gameObjects.push_back(new HarvesterCL(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    default: std::cout << "Tipo de unidad invalido" << std::endl;
                }
            } else if (type == 2) {
                m_protocol.recvBuild(m_socket, objectType, player, posX, posY, life);
            } else if (type == 3) {
                std::cout << "Se recibe un gusano de arena" << std::endl;
            } else {
                std::cout << "Error se recibio otro" << std::endl;
            }
        }
        m_quene.push(gameObjects);
    }
}

void RecvThread::stop() {
    running = false;
}



