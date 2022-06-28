//
// Created by riclui on 27/06/22.
//

#include "ButtonHeavyInfantryCL.h"

ButtonHeavyInfantryCL::ButtonHeavyInfantryCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BHEAVY_FACTORY, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}