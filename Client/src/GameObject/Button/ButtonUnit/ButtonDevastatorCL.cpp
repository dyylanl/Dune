//
// Created by riclui on 13/07/22.
//

#include "ButtonDevastatorCL.h"

ButtonDevastatorCL::ButtonDevastatorCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BDEVASTATOR, SDL2pp::Point(1190, 502), id, SARDAUKAR_KEY,player, constructionTime, selectStatus, ready) {}
