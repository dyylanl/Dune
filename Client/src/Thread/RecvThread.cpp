#include "RecvThread.h"

void RecvThread::run() {
    Unidad *unit = new Unidad();
    while (running) {
        //int *aux = new int;
        *unit = m_protocol.recvResponse(m_socket);
        std::cout << "Se agrega: " << *unit << std::endl;
        m_quene.push(unit);
    }
    delete unit;
}

void RecvThread::crearUnidad() {
    std::cout << "Se recibio el comando crear unidad.\n";
}

void RecvThread::stop() {
    m_eventManager.quit();
}
