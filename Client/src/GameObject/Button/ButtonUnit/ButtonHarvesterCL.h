//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONHARVESTERCL_H
#define DUNE_BUTTONHARVESTERCL_H


#include "ButtonUnitCL.h"

class ButtonHarvesterCL : public ButtonUnitCL {
public:
    ButtonHarvesterCL(int id,char player, int constructionTime, bool selectStatus, bool ready);

    ~ButtonHarvesterCL() {}
};


#endif //DUNE_BUTTONHARVESTERCL_H
