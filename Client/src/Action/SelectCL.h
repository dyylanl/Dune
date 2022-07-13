//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_SELECTCL_H
#define DUNE_SELECTCL_H


#include "CommandCL.h"

class SelectCL : public CommandCL{
private:
    SDL2pp::Point m_position;

public:
    SelectCL(SDL2pp::Point position) : m_position(position) {}

    void execute(Protocol &protocol, Socket &socket);

    ~SelectCL() {}
};


#endif //DUNE_SELECTCL_H
