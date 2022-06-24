//
// Created by riclui on 23/06/22.
//

#include "MoveCL.h"

void MoveCL::execute(Protocol &protocol, Socket &socket) {
    char action = 6;
    int posX = m_position.GetX();
    int posY = m_position.GetY();
    protocol.sendCommandMove(socket, action, m_id, posX, posY);
}
