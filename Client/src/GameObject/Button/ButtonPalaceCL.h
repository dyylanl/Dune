//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONPALACECL_H
#define DUNE_BUTTONPALACECL_H


#include "../Button.h"

class ButtonPalaceCL : public Button {
public:
    ButtonPalaceCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONPALACECL_H
