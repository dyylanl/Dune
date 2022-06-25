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

void SendThread::stop() {
    m_quene.close();
    running = false;
}