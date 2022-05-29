//
// Created by riclui on 28/05/22.
//

#ifndef DUNE_PLAYER_H
#define DUNE_PLAYER_H


#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"

class Player {
public:
    Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};


#endif //DUNE_PLAYER_H
