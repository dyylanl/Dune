//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONHEAVYINFANTRYCL_H
#define DUNE_BUTTONHEAVYINFANTRYCL_H


#include "../ButtonUnitCL.h"

class ButtonHeavyInfantryCL : public ButtonUnitCL{
public:
    ButtonHeavyInfantryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    ~ButtonHeavyInfantryCL() {}
};


#endif //DUNE_BUTTONHEAVYINFANTRYCL_H
