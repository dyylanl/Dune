//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONSARDAUKARCL_H
#define DUNE_BUTTONSARDAUKARCL_H


#include "ButtonUnitCL.h"

class ButtonSardaukarCL : public ButtonUnitCL {
public:
    ButtonSardaukarCL(int id, char player, int constructionTime, bool selectStatus, bool ready);
};


#endif //DUNE_BUTTONSARDAUKARCL_H
