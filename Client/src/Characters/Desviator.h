//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_DESVIATOR_H
#define DUNE_DESVIATOR_H


#include "Vehicle.h"

class Desviator : public Vehicle{
public:
    Desviator(SDL2pp::Point position, int id, int player, bool selecStatus, SDL2pp::Point posAction, int life, bool action);

    SDL2pp::Rect getShape();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_DESVIATOR_H
