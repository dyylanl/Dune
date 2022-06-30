//
// Created by riclui on 27/06/22.
//

#include "ButtonTankCL.h"

ButtonTankCL::ButtonTankCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BTANK, SDL2pp::Point(1114, 222), id, 't',player, constructionTime, selectStatus, ready) {}
