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
    Player(std::string textureID, TextureManager &manager);
    ~Player();
    void update(float dt);
    void draw(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation m_Animation;
    bool facingLeft;
    bool moving;
    int x;
    int y;
    std::string m_TextureID;
};

#endif //DUNE_PLAYER_H
