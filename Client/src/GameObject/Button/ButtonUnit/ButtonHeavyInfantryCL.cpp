//
// Created by riclui on 27/06/22.
//

#include "ButtonHeavyInfantryCL.h"

ButtonHeavyInfantryCL::ButtonHeavyInfantryCL(int id,char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BHEAVY_INFANTRY, SDL2pp::Point(1190, 432), id, HEAVY_INFANTRY_KEY, player, constructionTime, selectStatus, ready) {}