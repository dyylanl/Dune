//
// Created by riclui on 16/06/22.
//

#include "SendThread.h"

void SendThread::run() {
    try {
        while (running) {
            std::unique_ptr<CommandCL> action;
            if (m_quene.pop(action)) {
                action->execute(m_protocol, m_socket);
            }
        }
    } catch (Exception &e) {
        stop();
    }
}

void SendThread::stop() {
    running = false;
    m_quene.close();
}