//
// Created by riclui on 23/06/22.
//

#ifndef DUNE_BUTTONCONSTRUCTIONYARDCL_H
#define DUNE_BUTTONCONSTRUCTIONYARDCL_H


#include "../Button.h"

class ButtonConstructionYardCL : public Button {
public:
    ButtonConstructionYardCL(int id, char player, int constructionTime);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONCONSTRUCTIONYARDCL_H
