//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_DEVASTATORCL_H
#define DUNE_DEVASTATORCL_H


#include "../Vehicle.h"

class DevastatorCL : public Vehicle{
public:
    DevastatorCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action);

    SDL2pp::Rect getShape();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_DEVASTATORCL_H
