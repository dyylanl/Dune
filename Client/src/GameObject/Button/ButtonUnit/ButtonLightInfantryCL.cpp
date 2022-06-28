//
// Created by riclui on 27/06/22.
//

#include "ButtonLightInfantryCL.h"

ButtonLightInfantryCL::ButtonLightInfantryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BLIGHT_INFANTRY, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}