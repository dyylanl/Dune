//
// Created by riclui on 27/06/22.
//

#include "ButtonSardaukarCL.h"

ButtonSardaukarCL::ButtonSardaukarCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BSARDAUKAR, SDL2pp::Point(1190, 502), id, SARDAUKAR_KEY,player, constructionTime, selectStatus, ready) {}
