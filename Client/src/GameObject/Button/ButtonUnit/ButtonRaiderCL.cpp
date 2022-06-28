//
// Created by riclui on 27/06/22.
//

#include "ButtonRaiderCL.h"

ButtonRaiderCL::ButtonRaiderCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BRAIDER, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}
