//
// Created by riclui on 30/06/22.
//

#ifndef DUNE_BUTTONBUILDCL_H
#define DUNE_BUTTONBUILDCL_H


#include "../ButtonCL.h"
#include "../BuildCL.h"

class ButtonBuildCL : public ButtonCL{
protected:
    SDL2pp::Point m_positionBuild;

public:
    ButtonBuildCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime, bool selectStatus, bool ready);

    void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) = 0;

    virtual void buildBuilding(BQueue<std::unique_ptr<CommandCL>> &queue, SDL2pp::Point point) = 0;

    virtual ~ButtonBuildCL() {}
};


#endif //DUNE_BUTTONBUILDCL_H
