//
// Created by riclui on 27/06/22.
//

#include "ButtonHarvesterCL.h"

ButtonHarvesterCL::ButtonHarvesterCL(int id, char player,int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BHARVESTER, SDL2pp::Point(1190, 642), id, HARVESTER_KEY,player, constructionTime, selectStatus, ready) {}
