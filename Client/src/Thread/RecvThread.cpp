//
// Created by riclui on 11/06/22.
//

#include "RecvThread.h"

void RecvThread::run() {
    char operation = 0;
    while (m_eventManager.isRunnig()) {
        protocol.operationRecv(skt, operation);
        if(operation == 4) {
            crearUnidad();
        }
    }
    std::cout << "salir" << std::endl;
}

void RecvThread::crearUnidad() {
    int unitId = protocol.idUnidRecv(skt);
    char unitType = protocol.typeUnidRecv(skt);
    std::vector<int> pos = protocol.recvPosition(skt);
    if (unitType == 'T') {
        std::cout << "crear tank " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
        Player player1("missileTank", m_textureManager, SDL2pp::Point(pos[0] * 30, pos[1] * 30), SDL2pp::Point(34, 34));
        m_gameObjects.push_back(player1);
    }
    if (unitType == 'o') {
        std::cout << "crear otro: " << unitId << ":" << pos[0] << "," << pos[1] << std::endl;
        Player player1("carryall", m_textureManager, SDL2pp::Point(pos[0] * 30, pos[1] * 30), SDL2pp::Point(64, 61));
        m_gameObjects.push_back(player1);
    }
}

void RecvThread::stop() {

}
