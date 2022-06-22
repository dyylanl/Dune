//
// Created by riclui on 22/06/22.
//

#ifndef DUNE_CONSTRUCTIONYARDCL_H
#define DUNE_CONSTRUCTIONYARDCL_H


#include "../BuildCL.h"

class ConstructionYardCL : public BuildCL {
public:
    ConstructionYardCL(SDL2pp::Point position, int id, int player, int life);

    SDL2pp::Rect getShape();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);
};


#endif //DUNE_CONSTRUCTIONYARDCL_H
