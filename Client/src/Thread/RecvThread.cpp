#include "RecvThread.h"
#include "../Characters/Desviator.h"

void RecvThread::run() {
    while (running) {
        int type;
        int objectType;
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
                    case INFANTERIA_LIGERA: std::cout << "tipo: " << INFANTERIA_LIGERA << std::endl;
                        break;
                    case INFANTERIA_PESADA: std::cout << "tipo: " << INFANTERIA_PESADA << std::endl;
                        break;
                    case FREMEN: std::cout << "tipo: " << FREMEN << std::endl;
                        break;
                    case SARDAUKAR: std::cout << "tipo: " << SARDAUKAR << std::endl;
                        break;
                    case TRIKE: std::cout << "tipo: " << TRIKE << std::endl;
                        break;
                    case TANQUE_SONICO: std::cout << "tipo: " << TANQUE_SONICO << std::endl;
                        break;
                    case RAIDER: std::cout << "tipo: " << RAIDER << std::endl;
                        break;
                    case DESVIADOR:
                        m_protocol.recvUnit(m_socket, player, selectStatus , posX, posY, posActX, posActY, life, action);
                        gameObjects.push_back(new Desviator(SDL2pp::Point(posX, posY), 0, player, selectStatus, SDL2pp::Point(posActX, posActY), life, action));
                        break;
                    case TANQUE: std::cout << "tipo: " << TANQUE << std::endl;
                        break;
                    case DEVASTADOR: std::cout << "tipo: " << DEVASTADOR << std::endl;
                        break;
                    case COSECHADORA: std::cout << "tipo: " << COSECHADORA << std::endl;
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



