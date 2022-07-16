//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_TRIKECL_H
#define DUNE_TRIKECL_H


#include "../Vehicle.h"
#include "../../Animation/Animation.h"

class TrikeCL : public Vehicle{
private:
    int m_frameCount;
    int m_colCount;
    Animation m_animation;
public:
    TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
            bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~TrikeCL() {}

    SDL2pp::Point selectFrame();
};


#endif //DUNE_TRIKECL_H
