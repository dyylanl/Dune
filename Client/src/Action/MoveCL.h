//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_MOVECL_H
#define DUNE_MOVECL_H


#include "CommandCL.h"

class MoveCL : public CommandCL{
private:
    SDL2pp::Point m_position;
public:
    MoveCL(SDL2pp::Point position) : m_position(position) {}

    void execute(Protocol &protocol, Socket &socket);

    ~MoveCL() {}
};


#endif //DUNE_MOVECL_H
