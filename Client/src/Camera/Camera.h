//
// Created by riclui on 07/06/22.
//

#ifndef DUNE_CAMERA_H
#define DUNE_CAMERA_H

#include "SDL2pp/SDL2pp.hh"

class Camera {
private:
    SDL2pp::Point position;
public:
    Camera() : position(0,0) {}
    void update(SDL_Event &event);
    SDL2pp::Point getPosicion();
};


#endif //DUNE_CAMERA_H
