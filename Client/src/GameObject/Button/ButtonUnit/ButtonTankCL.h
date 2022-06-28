//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONTANKCL_H
#define DUNE_BUTTONTANKCL_H


#include "ButtonUnitCL.h"

class ButtonTankCL : public ButtonUnitCL {
public:
    ButtonTankCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    ~ButtonTankCL() {}
};


#endif //DUNE_BUTTONTANKCL_H
