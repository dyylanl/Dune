//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONTRIKECL_H
#define DUNE_BUTTONTRIKECL_H


#include "ButtonUnitCL.h"

class ButtonTrikeCL : public ButtonUnitCL{
public:
    ButtonTrikeCL(int id, char player, int constructionTime, bool selectStatus, bool ready);
};


#endif //DUNE_BUTTONTRIKECL_H
