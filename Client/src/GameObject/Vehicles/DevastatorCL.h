//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_DEVASTATORCL_H
#define DUNE_DEVASTATORCL_H


#include "../Vehicle.h"

class DevastatorCL : public Vehicle {
public:
    DevastatorCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                 bool action);

    ~DevastatorCL() {}
};


#endif //DUNE_DEVASTATORCL_H
