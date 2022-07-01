//
// Created by riclui on 30/06/22.
//

#ifndef DUNE_BUTTONBUILDCL_H
#define DUNE_BUTTONBUILDCL_H


#include "../ButtonCL.h"

class ButtonBuildCL : public ButtonCL{
public:
    ButtonBuildCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime, bool selectStatus, bool ready);

    void update(EventManager &eventManager, BQueue<std::unique_ptr<CommandCL>> &queue);

    virtual void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) = 0;

    virtual ~ButtonBuildCL() {}
};


#endif //DUNE_BUTTONBUILDCL_H
