//
// Created by riclui on 13/07/22.
//

#include "ButtonSonicTankCL.h"

ButtonSonicTankCL::ButtonSonicTankCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BSONIC_TANK, SDL2pp::Point(1190, 432), id, SONIC_TANK_KEY, player, constructionTime, selectStatus, ready) {}
