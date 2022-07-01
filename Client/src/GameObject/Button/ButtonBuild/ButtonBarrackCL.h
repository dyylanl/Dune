//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONBARRACKCL_H
#define DUNE_BUTTONBARRACKCL_H


#include "../ButtonBuildCL.h"

class ButtonBarrackCL : public ButtonBuildCL {
public:
    ButtonBarrackCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonBarrackCL() {}
};


#endif //DUNE_BUTTONBARRACKCL_H
