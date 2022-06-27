//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_SILOCL_H
#define DUNE_SILOCL_H


#include "../BuildCL.h"

class SiloCL : public BuildCL {
public:
    SiloCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_SILOCL_H
