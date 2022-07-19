//
// Created by riclui on 13/07/22.
//

#include "ButtonDesviatorCL.h"

ButtonDesviatorCL::ButtonDesviatorCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
        : ButtonUnitCL(BDESVIATOR, SDL2pp::Point(1190, 362), id, DESVIATOR_KEY, player, constructionTime, selectStatus, ready) {}
