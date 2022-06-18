//
// Created by riclui on 17/06/22.
//

#ifndef DUNE_UNITTYPE_H
#define DUNE_UNITTYPE_H


#include "Object.h"

class UnitType : public Object{

public:
    UnitType(int player, bool selectStatus, int posX, int posY, int posActX, int posActY, int life, bool action);
};


#endif //DUNE_UNITTYPE_H
