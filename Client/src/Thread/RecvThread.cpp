#include "RecvThread.h"
#include "../GameObject/Vehicles/DeviatorCL.h"
#include "../GameObject/Vehicles/TrikeCL.h"
#include "../GameObject/Vehicles/SonicTankCL.h"
#include "../GameObject/Vehicles/TankCL.h"
#include "../GameObject/Vehicles/DevastatorCL.h"
#include "../GameObject/Vehicles/HarvesterCL.h"
#include "../GameObject/Builds/ConstructionYardCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonWidtrapCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonConstructionYardCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonRefineryCL.h"
#include "../GameObject/Builds/LightFactoryCL.h"
#include "../GameObject/Builds/HeavyFactoryCL.h"
#include "../GameObject/Builds/WindTrapCL.h"
#include "../GameObject/Builds/RefineryCL.h"
#include "../GameObject/Builds/SiloCL.h"
#include "../GameObject/Builds/BarrackCL.h"
#include "../GameObject/Builds/PalaceCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonLightFactoryCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonHeavyFactoryCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonSiloCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonBarrackCL.h"
#include "../GameObject/Button/ButtonBuild/ButtonPalaceCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonTrikeCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonRaiderCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonTankCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonHarvesterCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonLightInfantryCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonHeavyInfantryCL.h"
#include "../GameObject/Button/ButtonUnit/ButtonSardaukarCL.h"

void RecvThread::run() {
    try {
        while (running) {
            char type = ' ';
            int size = 0;
            std::vector<std::unique_ptr<GameObject>> gameObjects;

            m_protocol.recvCountObject(m_socket, size);
            for (int i = 0; i < size; ++i) {
                m_protocol.recvType(m_socket, type);
                switch (type) {
                    case UNIT:
                        addVehicle(gameObjects);
                        break;
                    case BUILD:
                        addBuild(gameObjects);
                        break;
                    default:
                        std::cout << "Tipo invalido" << std::endl;
                }
            }
            m_quene.push(gameObjects);

            uint8_t opcode = 0;
            opcode = m_protocol.recvResponse(m_socket);
            if (opcode == 25) {
                int gold = 0;
                int energy = 0;
                m_protocol.recvPlayer(m_socket, gold, energy);
                /*std::cout << "oro: " << gold << std::endl;
                std::cout << "energia: " << energy << std::endl;*/
            }
        }
    } catch (Exception &e) {
        stop();
    }
}

void RecvThread::stop() {
    running = false;
    m_socket.shutdown();
}

void RecvThread::addVehicle(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
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
        case TRIKE_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new TrikeCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                                                    SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case SONIC_TANK_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new SonicTankCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                                              SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case RAIDER_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new TrikeCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                                          SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case DESVIATOR_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new DeviatorCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                 SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case TANK_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new TankCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                             SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case DEVASTATOR_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new DevastatorCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                   SDL2pp::Point(posActX, posActY), life, action)));
            break;
        case HARVESTER_KEY:
            m_protocol.recvUnit(m_socket, id, player, selectStatus, posX, posY, posActX,
                                posActY, life, action);
            gameObjects.push_back(std::unique_ptr<GameObject>(new HarvesterCL(id, player, selectStatus, SDL2pp::Point(posX, posY),
                                                  SDL2pp::Point(posActX, posActY), life, action)));
            break;
        default:
            std::cout << "Tipo de unidad invalido" << std::endl;
    }
}

void RecvThread::addBuild(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    char objectType = 0;
    int id = 0;
    char player = 0;
    int posX = 0;
    int posY = 0;
    int life = 0;

    m_protocol.recvObjectType(m_socket, objectType);
    switch (objectType) {
        case CONSTRUCTION_CENTER_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new ConstructionYardCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case LIGHT_FACTORY_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new LightFactoryCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case HEAVY_FACTORY_KEY :
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new HeavyFactoryCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case WIND_TRAP_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new WindTrapCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case REFINERY_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new RefineryCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case SILO_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new SiloCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case BARRACKS_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new BarrackCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        case PALACE_KEY:
            m_protocol.recvBuild(m_socket, id, player, posX, posY, life);
            gameObjects.push_back(std::unique_ptr<GameObject>(new PalaceCL(id, player, SDL2pp::Point(posX, posY), life)));
            break;
        default: std::cout << "Tipo de edificio invalido" << std::endl;
    }
}
