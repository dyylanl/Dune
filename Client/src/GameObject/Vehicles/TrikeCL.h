//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_TRIKECL_H
#define DUNE_TRIKECL_H


#include "../Vehicle.h"
#include "../../Animation/Animation.h"

class TrikeCL : public Vehicle{
public:
    TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
            bool action);

    ~TrikeCL() {}

    SDL2pp::Point selectFrame();
};


#endif //DUNE_TRIKECL_H
