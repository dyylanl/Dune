//
// Created by riclui on 07/06/22.
//

#ifndef DUNE_CAMERA_H
#define DUNE_CAMERA_H

#include "SDL2pp/SDL2pp.hh"
#include "../Events/EventManager.h"

class Camera {
private:
    SDL2pp::Point position;
public:
    Camera() : position(0,0) {}
    void update(EventManager &eventManager);
    SDL2pp::Point getPosicion();
};


#endif //DUNE_CAMERA_H
