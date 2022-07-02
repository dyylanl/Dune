//
// Created by riclui on 27/06/22.
//

#ifndef DUNE_BUTTONUNITCL_H
#define DUNE_BUTTONUNITCL_H


#include "../ButtonCL.h"

class ButtonUnitCL : public ButtonCL{
public:
    ButtonUnitCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime, bool selectStatus, bool ready);

    void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue);

    virtual ~ButtonUnitCL() {}
};


#endif //DUNE_BUTTONUNITCL_H
