//
// Created by riclui on 24/06/22.
//

#include "BuildBuilding.h"

void BuildBuilding::execute(Protocol &protocol, Socket &socket) {
    char action = 7;
    int posX = m_position.GetX();
    int posY = m_position.GetY();
    protocol.sendCommandBuildBuilding(socket, action, m_build, posX, posY);
}
