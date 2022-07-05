//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_PALACECL_H
#define DUNE_PALACECL_H


#include "../BuildCL.h"

class PalaceCL : public BuildCL {
public:
    PalaceCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~PalaceCL() {}
};


#endif //DUNE_PALACECL_H
