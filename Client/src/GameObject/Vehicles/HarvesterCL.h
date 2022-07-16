//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_HARVESTERCL_H
#define DUNE_HARVESTERCL_H


#include "../Vehicle.h"

class HarvesterCL : public Vehicle {
public:
    HarvesterCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                bool action);

    ~HarvesterCL() {}
};


#endif //DUNE_HARVESTERCL_H
