//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONREFINERYCL_H
#define DUNE_BUTTONREFINERYCL_H


#include "../../../Graphics/TextureManager.h"
#include "../../ButtonCL.h"

class ButtonRefineryCL : public ButtonCL {
public:
    ButtonRefineryCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONREFINERYCL_H
