//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H


#include "SDL2pp/SDL2pp.hh"
#include "../Animation/Animation.h"
#include "../Graphics/TextureManager.h"

class Player {
public:
    Player(std::string textureID, TextureManager &manager, int X, int Y);
    ~Player();
    void update(float dt);
    void draw(SDL2pp::Renderer &renderer);

private:
    Animation m_Animation;
    int x;
    int y;
    std::string m_TextureID;
};

#endif //DUNE_PLAYER_H
