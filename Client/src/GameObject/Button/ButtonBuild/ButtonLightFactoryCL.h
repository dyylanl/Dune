//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONLIGHTFACTORYCL_H
#define DUNE_BUTTONLIGHTFACTORYCL_H


#include "../../ButtonCL.h"

class ButtonLightFactoryCL : public ButtonCL {
public:
    ButtonLightFactoryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);

    ~ButtonLightFactoryCL() {}
};


#endif //DUNE_BUTTONLIGHTFACTORYCL_H
