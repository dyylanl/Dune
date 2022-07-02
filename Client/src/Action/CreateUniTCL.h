//
// Created by riclui on 30/06/22.
//

#ifndef DUNE_CREATEUNITCL_H
#define DUNE_CREATEUNITCL_H


#include "CommandCL.h"

class CreateUniTCL  : public CommandCL{
private:
    char m_unitType;

public:
    CreateUniTCL(char unitType) : m_unitType(unitType) {}

    void execute(Protocol &protocol, Socket &socket);

    ~CreateUniTCL() {}
};


#endif //DUNE_CREATEUNITCL_H
