//
// Created by riclui on 11/06/22.
//

#include "ClientThread.h"

void ClientThread::run() {
    char operation = 0;
    while (m_eventManager.isRunnig()) {
        protocol.operationRecv(skt, operation);
        if(operation == 4) {
            crearUnidad();
        }
    }
    std::cout << "salir" << std::endl;
}

void ClientThread::crearUnidad() {
    int unitId = protocol.idUnidRecv(skt);
    char unitType = protocol.typeUnidRecv(skt);
    std::vector<int> pos = protocol.recvPosition(skt);
    if (unitType == 't') {
        std::cout << "crear tank " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
    }
    if (unitType == 'o') {
        std::cout << "crear otro: " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
    }
}
