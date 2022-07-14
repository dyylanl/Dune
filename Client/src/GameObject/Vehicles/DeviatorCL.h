//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_DEVIATORCL_H
#define DUNE_DEVIATORCL_H


#include "../Vehicle.h"

class DeviatorCL : public Vehicle{
public:
    DeviatorCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
               bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~DeviatorCL() {}
};


#endif //DUNE_DEVIATORCL_H
