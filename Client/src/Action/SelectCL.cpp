//
// Created by riclui on 23/06/22.
//

#include "SelectCL.h"

void SelectCL::execute(Protocol &protocol, Socket &socket) {
    char action = 5;
    int posX = m_position.GetX();
    int posY = m_position.GetY();
    protocol.sendCommandSelect(socket, action, posX, posY);
}
