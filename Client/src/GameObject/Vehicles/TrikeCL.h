//
// Created by riclui on 21/06/22.
//

#ifndef DUNE_TRIKECL_H
#define DUNE_TRIKECL_H


#include "../Vehicle.h"

class TrikeCL : public Vehicle{
private:
    int m_framesSize;
    int cantCol;
    int cantFil;
public:
    TrikeCL(int id, int player, bool selecStatus, SDL2pp::Point position, SDL2pp::Point posAction, int life,
            bool action);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera);

    ~TrikeCL() {}

    SDL2pp::Point posFrame();
};


#endif //DUNE_TRIKECL_H
