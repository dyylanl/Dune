//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_SELECTCL_H
#define DUNE_SELECTCL_H


#include "CommandCL.h"

class SelectCL : public CommandCL{
private:
    int m_id;

public:
    SelectCL(int id) : m_id(id) {}

    void execute(Protocol &protocol, Socket &socket);
};


#endif //DUNE_SELECTCL_H
