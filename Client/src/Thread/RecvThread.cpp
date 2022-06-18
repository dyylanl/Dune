#include "RecvThread.h"
#include "../Characters/UnitType.h"

void RecvThread::run() {
    Object *unit = new Object();
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
        m_protocol.recvCountObject(m_socket, size);
        for (int i = 0; i < size; ++i) {
            m_protocol.recvType(m_socket, type);
            if (type == 1) {
                m_protocol.recvUnit(m_socket, objectType, player, selectStatus , posX, posY, posActX, posActY, life, action);
                if(objectType == 1) {
                    //unitType = "Infantería Ligera";
                }
                if(objectType == 2) {
                    //unitType = "Infantería Pesada";
                }
                if(objectType == 3) {
                    //unitType = "Fremen";
                }
                if(objectType == 4) {
                    //unitType = "Sardaukar";
                }
                if(objectType == 5) {
                    //unitType = "Trike";
                }
                if(objectType == 6) {
                    //unitType = "Tanque Sonico";
                }
                if(objectType == 7) {
                    //unitType = "Raider";
                }
                if(objectType == 8) {
                    //unitType = "Desviador";
                }
                if(objectType == 6) {
                    //unitType = "Tanque";
                    unit = new UnitType(player, selectStatus , posX, posY, posActX, posActY, life, action);
                    //unit->set(objectType, player, posX, posY, posActX, posActY, life, action);
                }
                if(objectType == 7) {
                    //unitType = "Devastador";
                }
                if(objectType == 8) {
                    //unitType = "Cosechadora";
                }
            } else if (type == 2) {
                std::cout << "Se recibe un Edificio" << std::endl;
            } else if (type == 3) {
                std::cout << "Se recibe un gusano de arena" << std::endl;
            } else {
                std::cout << "Error se recibio otro" << std::endl;
            }
            m_quene.push(unit);
        }
    }
    delete unit;
}

void RecvThread::stop() {
    running = false;
}



