//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONBARRACK_H
#define DUNE_BUTTONBARRACK_H


#include "../Button.h"

class ButtonBarrack : public Button {
public:
    ButtonBarrack(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONBARRACK_H
