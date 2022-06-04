//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H


#include "SDL2pp/SDL2pp.hh"
#include "../Animation/Animation.h"
#include "../Graphics/TextureManager.h"
#include "../Events/EventManager.h"

class Player {
private:
    Animation m_Animation;
    int x;
    int y;
    std::string m_TextureID;

public:
    Player(std::string textureID, TextureManager &manager, int X, int Y);
    ~Player();
    void update(EventManager &eventManager, float dt);
    void draw(SDL2pp::Renderer &renderer);
    SDL2pp::Rect getShape();
};

#endif //DUNE_PLAYER_H
