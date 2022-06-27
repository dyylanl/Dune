//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_BARRACKCL_H
#define DUNE_BARRACKCL_H


#include "../BuildCL.h"

class BarrackCL : public BuildCL {
public:
    BarrackCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_BARRACKCL_H
