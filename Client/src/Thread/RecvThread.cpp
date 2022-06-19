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
                unit = createUnit(objectType, player, selectStatus, posX, posY, posActX, posActY, life, action);
            } else if (type == 2) {
                m_protocol.recvBuild(m_socket, objectType, player, posX, posY, life);
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

Object *
RecvThread::createUnit(int objectType, int player, bool selectStatus, int posX, int posY, int posActX, int posActY,
                       int life, bool action) const {
    Object *unit = new Object();
    if (objectType == 1) {
        unit = new UnitType("InfanteríaLigera", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 2) {
        unit = new UnitType("InfanteríaPesada", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 3) {
        unit = new UnitType("Fremen", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 4) {
        unit = new UnitType("Sardaukar", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 5) {
        unit = new UnitType("Trike", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 6) {
        unit = new UnitType("TanqueSonico", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 7) {
        unit = new UnitType("Raider", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 8) {
        unit = new UnitType("Desviador", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 9) {
        unit = new UnitType("Tanque", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 10) {
        unit = new UnitType("Devastador", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else if (objectType == 11) {
        unit = new UnitType("Cosechadora", player, selectStatus , posX, posY, posActX, posActY, life, action);
    } else {
        std::cout << "Invalid type unit";
    }
    return unit;
}

void RecvThread::stop() {
    running = false;
}



