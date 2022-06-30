//
// Created by riclui on 27/06/22.
//

#include "ButtonTrikeCL.h"

ButtonTrikeCL::ButtonTrikeCL(int id, char player, int constructionTime, bool selectStatus, bool ready)
: ButtonUnitCL(BTRIKE, SDL2pp::Point(1190, 222), id, 'a',player, constructionTime, selectStatus, ready) {}
