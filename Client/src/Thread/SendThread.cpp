//
// Created by riclui on 16/06/22.
//

#include "SendThread.h"

void SendThread::run() {
    try {
        while (running) {
            std::unique_ptr<CommandCL> action;
            action = m_quene.front();
            m_quene.pop();
            action->execute(m_protocol, m_socket);
        }
    } catch (ClosedQueue & e) {
        std::cerr << e.what() << std::endl;
    }
}

void SendThread::stop() {
    running = false;
    m_quene.close();
}