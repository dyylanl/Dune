//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONRAIDERCL_H
#define DUNE_BUTTONRAIDERCL_H


#include "ButtonUnitCL.h"

class ButtonRaiderCL : public ButtonUnitCL{
public:
    ButtonRaiderCL(int id, char player, int constructionTime, bool selectStatus, bool ready);
};


#endif //DUNE_BUTTONRAIDERCL_H
