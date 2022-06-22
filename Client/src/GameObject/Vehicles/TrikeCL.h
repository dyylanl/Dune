//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_TRIKECL_H
#define DUNE_TRIKECL_H


#include "../Vehicle.h"

class TrikeCL : public Vehicle{
public:
    TrikeCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_TRIKECL_H
