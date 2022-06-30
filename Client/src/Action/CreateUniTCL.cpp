//
// Created by riclui on 30/06/22.
//

#include "CreateUniTCL.h"

void CreateUniTCL::execute(Protocol &protocol, Socket &socket) {
    char action = 8;
    protocol.sendCommandSelect(socket, action, m_unitType);
}
