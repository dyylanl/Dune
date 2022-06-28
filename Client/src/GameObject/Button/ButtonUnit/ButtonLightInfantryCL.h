//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONLIGHTINFANTRYCL_H
#define DUNE_BUTTONLIGHTINFANTRYCL_H


#include "ButtonUnitCL.h"

class ButtonLightInfantryCL : public ButtonUnitCL{
public:
    ButtonLightInfantryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    ~ButtonLightInfantryCL() {}
};


#endif //DUNE_BUTTONLIGHTINFANTRYCL_H
