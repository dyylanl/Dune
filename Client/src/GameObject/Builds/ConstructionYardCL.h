//
// Created by riclui on 22/06/22.
//

#ifndef DUNE_CONSTRUCTIONYARDCL_H
#define DUNE_CONSTRUCTIONYARDCL_H


#include "../BuildCL.h"

class ConstructionYardCL : public BuildCL {
public:
    ConstructionYardCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_CONSTRUCTIONYARDCL_H
