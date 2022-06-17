#include "RecvThread.h"

void RecvThread::run() {
    Unidad *unit = new Unidad();
    while (running) {
        int type;
        std::string objectType;
        int player;
        int posX;
        int posY;
        int posActX;
        int posActY;
        int life;
        bool action;
        m_protocol.recvType(m_socket, type);
        if (type == 1) {
            m_protocol.recvUnit(m_socket, objectType, player, posX, posY, posActX, posActY, life, action);
        } else if (type == 2) {
            std::cout << "Se recibe un Edificio" << std::endl;
        } else if (type == 3) {
            std::cout << "Se recibe un gusano de arena" << std::endl;
        } else {
            std::cout << "Error se recibio otro" << std::endl;
        }
        unit->set(objectType, player, posX, posY, posActX, posActY, life, action);
        m_quene.push(unit);
    }
    delete unit;
}

void RecvThread::stop() {
    running = false;
}



