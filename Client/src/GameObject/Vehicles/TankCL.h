//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_TANKCL_H
#define DUNE_TANKCL_H


#include "../Vehicle.h"

class TankCL : public Vehicle{
public:
    TankCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
           bool action);

    ~TankCL() {}
};


#endif //DUNE_TANKCL_H
