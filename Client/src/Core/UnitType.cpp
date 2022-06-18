//
// Created by riclui on 17/06/22.
//

#include "../Characters/UnitType.h"

UnitType::UnitType(int player, bool selectStatus, int posX, int posY, int posActX, int posActY, int life,
                   bool action) :
        Object("Tanque", player, selectStatus, posX, posY, posActX, posActY, life, action){}
