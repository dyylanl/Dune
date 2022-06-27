//
// Created by riclui on 27/06/22.
//

#include "ButtonHarvesterCL.h"

ButtonHarvesterCL::ButtonHarvesterCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BHARVESTER, SDL2pp::Point(1114, 222), id, player, constructionTime, selectStatus, ready) {}
