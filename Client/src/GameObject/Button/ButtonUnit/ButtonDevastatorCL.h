//
// Created by riclui on 13/07/22.
//

#ifndef DUNE_BUTTONDEVASTATORCL_H
#define DUNE_BUTTONDEVASTATORCL_H


#include "../ButtonUnitCL.h"

class ButtonDevastatorCL : public ButtonUnitCL {
public:
    ButtonDevastatorCL(int id, char player, int constructionTime, bool selectStatus, bool ready);
    ~ButtonDevastatorCL() {}
};


#endif //DUNE_BUTTONDEVASTATORCL_H
