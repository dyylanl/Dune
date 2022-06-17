//
// Created by riclui on 16/06/22.
//

#include "SendThread.h"

void SendThread::run() {
    while (running) {
        Action *action;
        action = m_quene.pop();
        if(action != nullptr) {
            int actionType = 0;
            int id = 0;
            int object = 0;
            int posX = 0;
            int posY = 0;
            actionType = action->getAction();
            m_protocol.sendType(m_socket, actionType);
            if (actionType == 5) {
                id = action->getId();
                m_protocol.sendId(m_socket, id);
            }
            if (actionType == 6) {
                id = action->getId();
                posX = action->getPosX();
                posY = action->getPosY();
                m_protocol.sendAction(m_socket, id, posX, posY);
            } else if (actionType == 7) {
                object = action->getObject();
                posX = action->getPosX();
                posY = action->getPosY();
                m_protocol.sendBuild(m_socket, object, posX, posY);
            } else if (actionType == 8) {
                object = action->getObject();
                m_protocol.sendUnit(m_socket, object);
            } else {
                std::cout << "Error actionType no valido" << std::endl;
            }
        }
    }
}

void SendThread::stop() {
    running = false;
}