//
// Created by riclui on 20/06/22.
//

#ifndef DUNE_BUTTONCL_H
#define DUNE_BUTTONCL_H

#include "SDL2pp/SDL2pp.hh"
#include "../Graphics/TextureManager.h"
#include "../Object/GameObject.h"


class ButtonCL : public GameObject{
protected:
    int m_id;
    char m_type;
    char m_player;
    int m_time;
    bool m_selectStatus;
    bool m_ready;

public:
    ButtonCL(char textureID, SDL2pp::Point position, int id, char type, char player, int actionTime, bool selectStatus, bool ready);

    virtual void processEvent(SDL_Event &event, BQueue<std::unique_ptr<CommandCL>> &queue, Camera &camera) = 0;

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    virtual ~ButtonCL() {}
};


#endif //DUNE_BUTTONCL_H
