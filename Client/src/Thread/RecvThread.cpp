#include "RecvThread.h"
#include "../GameObject/Vehicles/DeviatorCL.h"
#include "../GameObject/Vehicles/TrikeCL.h"
#include "../GameObject/Vehicles/SonicTankCL.h"
#include "../GameObject/Vehicles/TankCL.h"
#include "../GameObject/Vehicles/DevastatorCL.h"
#include "../GameObject/Vehicles/HarvesterCL.h"
#include "../GameObject/Builds/ConstructionYardCL.h"
#include "../GameObject/Button/ButtonWidtrap.h"
#include "../GameObject/Button/ButtonConstructionYardCL.h"
#include "../GameObject/Button/ButtonRefinery.h"
#include "../GameObject/Builds/LightFactoryCL.h"
#include "../GameObject/Builds/HeavyFactoryCL.h"
#include "../GameObject/Builds/WindTrapCL.h"
#include "../GameObject/Builds/RefineryCL.h"
#include "../GameObject/Builds/SiloCL.h"
#include "../GameObject/Builds/BarrackCL.h"
#include "../GameObject/Builds/PalaceCL.h"
#include "../GameObject/Button/ButtonLightFactoryCL.h"
#include "../GameObject/Button/ButtonHeavyFactoryCL.h"
#include "../GameObject/Button/ButtonSilo.h"
#include "../GameObject/Button/ButtonBarrack.h"
#include "../GameObject/Button/ButtonPalaceCL.h"

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
    }
}

void RecvThread::stop() {
    running = false;
    m_socket.shutdown();
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
            gameObjects.push_back(new TrikeCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                              SDL2pp::Point(posActX, posActY), life, action));
            break;
        case SONIC_TANK:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new SonicTankCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                  SDL2pp::Point(posActX, posActY), life, action));
            break;
        case RAIDER:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new TrikeCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                              SDL2pp::Point(posActX, posActY), life, action));
            break;
        case DESVIATOR:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new DeviatorCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                 SDL2pp::Point(posActX, posActY), life, action));
            break;
        case TANK:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new TankCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                             SDL2pp::Point(posActX, posActY), life, action));
            break;
        case DEVASTATOR:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new DevastatorCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                   SDL2pp::Point(posActX, posActY), life, action));
            break;
        case HARVESTER:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(new HarvesterCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
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
            gameObjects.push_back(new ConstructionYardCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case LIGHT_FACTORY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new LightFactoryCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case HEAVY_FACTORY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new HeavyFactoryCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case WIND_TRAP:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new WindTrapCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case REFINERY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new RefineryCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case SILO:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new SiloCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case BARRACK:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new BarrackCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        case PALACE:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(new PalaceCL(id, player, SDL2pp::Point(posX, posY), life));
            break;
        default: std::cout << "Tipo de edificio invalido" << std::endl;
    }
}

void RecvThread::addButton(std::vector<GameObject *> &gameObjects) {
    char objectType = 0;
    int id = 0;
    char player = 0;
    int constructionTime = 0;
    bool selectStatus = false;
    bool ready = false;

    m_protocol.recvObjectType(m_socket, objectType);
    switch (objectType) {
        case BCONSTRUCTION_YARD:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonConstructionYardCL(id, player, constructionTime, selectStatus, ready));
            break;
        case BLIGHT_FACTORY:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonLightFactoryCL(id, player, constructionTime, selectStatus, ready));
            break;
        case BHEAVY_FACTORY:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonHeavyFactoryCL(id, player, constructionTime, selectStatus, ready));
            break;
        case BWIND_TRAP:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonWidtrap(id, player, constructionTime, selectStatus, ready));
            break;
        case BREFINERY:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonRefinery(id, player, constructionTime, selectStatus, ready));
            break;
        case BSILO:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonSilo(id, player, constructionTime, selectStatus, ready));
            break;
        case BBARRACK:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonBarrack(id, player, constructionTime, selectStatus, ready));
            break;
        case BPALACE:
            m_protocol.recvBotton(m_socket, id, player, constructionTime, selectStatus, ready);
            gameObjects.push_back(new ButtonPalaceCL(id, player, constructionTime, selectStatus, ready));
            break;
        default: std::cout << "Tipo de button edificio invalido" << std::endl;
    }
}



