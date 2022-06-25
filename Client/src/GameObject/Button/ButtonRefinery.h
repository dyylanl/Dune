//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONREFINERY_H
#define DUNE_BUTTONREFINERY_H


#include "../../Graphics/TextureManager.h"
#include "../Button.h"

class ButtonRefinery : public Button {
public:
    ButtonRefinery(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONREFINERY_H
