//
// Created by riclui on 13/07/22.
//

#ifndef DUNE_BUTTONDESVIATORCL_H
#define DUNE_BUTTONDESVIATORCL_H


#include "../ButtonUnitCL.h"

class ButtonDesviatorCL : public ButtonUnitCL {
public:
    ButtonDesviatorCL(int id, char player, int constructionTime, bool selectStatus, bool ready);
    ~ButtonDesviatorCL() {}
};


#endif //DUNE_BUTTONDESVIATORCL_H
