//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONWIDTRAPCL_H
#define DUNE_BUTTONWIDTRAPCL_H


#include "../ButtonBuildCL.h"

class ButtonWidtrapCL : public ButtonBuildCL{
public:
    ButtonWidtrapCL(int id, char player, int constructionTime, bool selectStatus, bool ready);

    void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point);

    ~ButtonWidtrapCL() {}
};


#endif //DUNE_BUTTONWIDTRAPCL_H
