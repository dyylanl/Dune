//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONHEAVYFACTORYCL_H
#define DUNE_BUTTONHEAVYFACTORYCL_H


#include "../../ButtonCL.h"

class ButtonHeavyFactoryCL : public ButtonCL {
public:
    ButtonHeavyFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONHEAVYFACTORYCL_H
