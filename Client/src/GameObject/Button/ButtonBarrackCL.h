//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONBARRACKCL_H
#define DUNE_BUTTONBARRACKCL_H


#include "../ButtonBuild.h"

class ButtonBarrackCL : public ButtonBuild {
public:
    ButtonBarrackCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BlockingQueue<CommandCL *> &queue, SDL2pp::Point point);
};


#endif //DUNE_BUTTONBARRACKCL_H
