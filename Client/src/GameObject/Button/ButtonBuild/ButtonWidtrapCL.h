//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONWIDTRAPCL_H
#define DUNE_BUTTONWIDTRAPCL_H


#include "SDL2pp/SDL2pp.hh"
#include "../../../Graphics/TextureManager.h"
#include "../../ButtonCL.h"

class ButtonWidtrapCL : public ButtonCL{
public:
    ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONWIDTRAPCL_H
