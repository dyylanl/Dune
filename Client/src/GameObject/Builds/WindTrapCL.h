//
// Created by riclui on 26/06/22.
//

#ifndef DUNE_WINDTRAPCL_H
#define DUNE_WINDTRAPCL_H


#include "../BuildCL.h"

class WindTrapCL : public BuildCL {
public:
    WindTrapCL(int id, int player, SDL2pp::Point position, int life);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~WindTrapCL() {}
};


#endif //DUNE_WINDTRAPCL_H
