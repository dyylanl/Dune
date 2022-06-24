//
// Created by riclui on 16/06/22.
//

#include "SendThread.h"

void SendThread::run() {
    while (running) {
        CommandCL *action;
        action = m_quene.pop();
        if(action != nullptr) {
            action->execute(m_protocol, m_socket);
        }
    }
}

/*void SendThread::actionProcess(const CommandCL *action) {
    int actionType = 0;
    actionType = action->getAction();
    m_protocol.sendType(m_socket, actionType);
    if (actionType == 5 || actionType == 6) {
        m_protocol.sendPosition(m_socket, action->getPosX(), action->getPosY());
    } else if (actionType == 7) {
        m_protocol.sendBuild(m_socket, action->getObject(), action->getPosX(), action->getPosY());
    } else if (actionType == 8) {
        m_protocol.sendUnit(m_socket, action->getObject());
    } else {
        std::cout << "Error actionType no valido" << std::endl;
    }
}*/

void SendThread::stop() {
    m_quene.close();
    running = false;
}