//
// Created by riclui on 27/06/22.
//

#include "ButtonRaiderCL.h"

ButtonRaiderCL::ButtonRaiderCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BRAIDER, SDL2pp::Point(1190, 292), id, RAIDER_KEY,player, constructionTime, selectStatus, ready) {}
