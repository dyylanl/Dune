//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BUTTONSILOCL_H
#define DUNE_BUTTONSILOCL_H


#include "../ButtonBuildCL.h"

class ButtonSiloCL : public ButtonBuildCL{
public:
    ButtonSiloCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonSiloCL() {}
};


#endif //DUNE_BUTTONSILOCL_H
