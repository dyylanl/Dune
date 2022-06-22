//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_HARVESTERCL_H
#define DUNE_HARVESTERCL_H


#include "../Vehicle.h"

class HarvesterCL : public Vehicle {
public:
    HarvesterCL(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

};


#endif //DUNE_HARVESTERCL_H
