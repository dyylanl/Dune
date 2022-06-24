//
// Created by riclui on 24/06/22.
//

#ifndef DUNE_BUILDBUILDING_H
#define DUNE_BUILDBUILDING_H

#include "CommandCL.h"

class BuildBuilding : public CommandCL{
private:
    char m_build;
    SDL2pp::Point m_position;

public:
    BuildBuilding(char build, SDL2pp::Point position) : m_build(build), m_position(position) {}
    void execute(Protocol &protocol, Socket &socket);
};


#endif //DUNE_BUILDBUILDING_H
