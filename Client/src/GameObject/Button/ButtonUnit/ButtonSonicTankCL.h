//
// Created by riclui on 13/07/22.
//

#ifndef DUNE_BUTTONSONICTANKCL_H
#define DUNE_BUTTONSONICTANKCL_H


#include "../ButtonUnitCL.h"

class ButtonSonicTankCL : public ButtonUnitCL {
public:
    ButtonSonicTankCL(int id,char player, int constructionTime, bool selectStatus, bool ready);
    ~ButtonSonicTankCL() {}
};


#endif //DUNE_BUTTONSONICTANKCL_H
