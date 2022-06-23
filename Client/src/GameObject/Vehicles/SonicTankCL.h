//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_SONICTANKCL_H
#define DUNE_SONICTANKCL_H


#include "../Vehicle.h"

class SonicTankCL : public Vehicle{
public:
    SonicTankCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
                bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_SONICTANKCL_H
