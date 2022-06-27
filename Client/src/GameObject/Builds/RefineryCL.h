//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_REFINERYCL_H
#define DUNE_REFINERYCL_H


#include "../BuildCL.h"

class RefineryCL : public BuildCL {
public:
    RefineryCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_REFINERYCL_H
