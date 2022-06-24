//
// Created by riclui on 23/06/22.
//

#include "SelectCL.h"

void SelectCL::execute(Protocol &protocol, Socket &socket) {
    char action = 5;
    protocol.sendCommandSelect(socket, action, m_id);
}
