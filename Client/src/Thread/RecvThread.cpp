#include "RecvThread.h"

void RecvThread::run() {
    while (m_eventManager.isRunnig()) {
        protocol.recvCommand(skt);
    }
}

void RecvThread::crearUnidad() {
    std::cout << "Se recibio el comando crear unidad.\n";
}

void RecvThread::stop() {
    m_eventManager.quit();
}
