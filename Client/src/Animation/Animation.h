//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_ANIMATION_H
#define DUNE_ANIMATION_H

#include "SDL2pp/SDL2pp.hh"
#include "../Camera/Camera.h"
#include "../Graphics/TextureManager.h"

class Animation {
private:
    int m_frameCount;
    int m_colCount;
    SDL2pp::Point m_size;
    SDL2pp::Point m_position;
    SDL2pp::Point m_posAction;
    int m_player;
    int m_life;
    bool m_selectStatus;
    bool m_action;

public:
    Animation(int frameCount, int colCount, SDL2pp::Point size, SDL2pp::Point position, SDL2pp::Point posAction, int player, int life, bool selectStatus, bool action);
    ~Animation() {}

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager,char textureID, Camera &camera);

    SDL2pp::Point selectFrame();
};


#endif //DUNE_ANIMATION_H
