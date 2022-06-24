//
// Created by riclui on 16/06/22.
//

#ifndef DUNE_COMMANDCL_H
#define DUNE_COMMANDCL_H

#include "SDL2pp/Point.hh"
#include "../../../Common/includes/Protocol.h"

class CommandCL {
public:
    virtual void execute(Protocol &protocol, Socket &socket) = 0;
};


#endif //DUNE_COMMANDCL_H
