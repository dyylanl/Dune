#include "RecvThread.h"
#include "../GameObject/Vehicles/DeviatorCL.h"
#include "../GameObject/Vehicles/TrikeCL.h"
#include "../GameObject/Vehicles/SonicTankCL.h"
#include "../GameObject/Vehicles/TankCL.h"
#include "../GameObject/Vehicles/DevastatorCL.h"
#include "../GameObject/Vehicles/HarvesterCL.h"
#include "../GameObject/Builds/ConstructionYardCL.h"
#include "../GameObject/Button/ButtonWidtrap.h"

void RecvThread::run() {
    while (running) {
        char type;
        int size;
        std::vector<GameObject*> gameObjects;

        m_protocol.recvCountObject(m_socket, size);
        for (int i = 0; i < size; ++i) {
            m_protocol.recvType(m_socket, type);
            switch (type) {
                case VEHICLE: addVehicle(gameObjects);
                    break;
                case BUILD: addBuild(gameObjects);
                    break;
                case BUTTON: addButton(gameObjects);
                    break;
                default: std::cout << "Tipo invalido" << std::endl;
            }
        }
        m_quene.push(gameObjects);
        int aux;
        std::cin >> aux;
    }
}

void RecvThread::stop() {
    running = false;
}

void RecvThread::addVehicle(std::vector<GameObject*> &gameObjects) {
    char objectType = 0;
    int id = 0;
    char player = 0;
    bool selectStatus = false;
    int posX = 0;
    int posY = 0;
    int posActX = 0;
    int posActY = 0;
    int life = 0;
    bool action = false;

    m_protocol.recvObjectType(m_socket, objectType);
    switch (objectType) {
        case TRIKE:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new TrikeCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                              SDL2pp::Point(posActX, posActY), life, action));
            break;
        case SONIC_TANK:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new SonicTankCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                                  SDL2pp::Point(posActX, posActY), life, action));
            break;
        case RAIDER:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new TrikeCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                              SDL2pp::Point(posActX, posActY), life, action));
            break;
        case DESVIATOR:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new DeviatorCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                                 SDL2pp::Point(posActX, posActY), life, action));
            break;
        case TANK:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new TankCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                             SDL2pp::Point(posActX, posActY), life, action));
            break;
        case DEVASTATOR:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new DevastatorCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                                   SDL2pp::Point(posActX, posActY), life, action));
            break;
        case HARVESTER:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new HarvesterCL(SDL2pp::Point(posX, posY), 0, player, selectStatus,
                                                  SDL2pp::Point(posActX, posActY), life, action));
            break;
        default:
            std::cout << "Tipo de unidad invalido" << std::endl;
    }
}

void RecvThread::addBuild(std::vector<GameObject *> &gameObjects) {
    char objectType = 0;
    int id = 0;
    char player = 0;
    int posX = 0;
    int posY = 0;
    int life = 0;

    m_protocol.recvObjectType(m_socket, objectType);
    switch (objectType) {
        case CONSTRUCTION_YARD:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new ConstructionYardCL(SDL2pp::Point(posX, posY), id, player, life));
            break;
        case LIGHT_FACTORY: //Hacer Factory
            break;
        case HEAVY_FACTORY: //Hacer la clase HeavyFactory
            break;
        case WIND_TRAP: //Hacer la clase WindTrap
            break;
        case SPICE_REFINERY: //Hacer la clase SpiceRefinery
            break;
        case SPICE_SILO: //Hacer la clase SpiceSilo
            break;
        case BARRACKS: //Hacer la clase Barracks
            break;
        case PALACE: //Hacer la clase Palace
            break;
        default: std::cout << "Tipo de edificio invalido" << std::endl;
    }
}

void RecvThread::addButton(std::vector<GameObject *> &gameObjects) {
    char objectType = 0;
    int id = 0;
    char player = 0;
    int posX = 0;
    int posY = 0;
    int life = 0;

    m_protocol.recvObjectType(m_socket, objectType);
    switch (objectType) {
        case CONSTRUCTION_YARD: //Hacer la clase Yard
            break;
        case LIGHT_FACTORY: //Hacer Factory
            break;
        case HEAVY_FACTORY: //Hacer la clase HeavyFactory
            break;
        case WIND_TRAP:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            //gameObjects.push_back(new ButtonWidtrap(SDL2pp::Point(posX, posY), id, player, life));
            break;
        case SPICE_REFINERY: //Hacer la clase SpiceRefinery
            break;
        case SPICE_SILO: //Hacer la clase SpiceSilo
            break;
        case BARRACKS: //Hacer la clase Barracks
            break;
        case PALACE: //Hacer la clase Palace
            break;
        default: std::cout << "Tipo de edificio invalido" << std::endl;
    }
}



