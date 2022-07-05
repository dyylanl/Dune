//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_HEAVYFACTORYCL_H
#define DUNE_HEAVYFACTORYCL_H


#include "../BuildCL.h"

class HeavyFactoryCL : public BuildCL {
public:
    HeavyFactoryCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~HeavyFactoryCL() {}
};


#endif //DUNE_HEAVYFACTORYCL_H
