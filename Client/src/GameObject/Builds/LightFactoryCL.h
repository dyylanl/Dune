//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_LIGHTFACTORYCL_H
#define DUNE_LIGHTFACTORYCL_H


#include "../BuildCL.h"

class LightFactoryCL : public BuildCL {
public:
    LightFactoryCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~LightFactoryCL() {}
};


#endif //DUNE_LIGHTFACTORYCL_H
