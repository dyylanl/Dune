//
// Created by riclui on 07/06/22.
//

#ifndef DUNE_CAMERA_H
#define DUNE_CAMERA_H

#include "SDL2pp/SDL2pp.hh"

#define GAME_WIDTH 1089
#define GAME_HEIGHT 720


class Camera {
private:
    SDL2pp::Rect m_viewBox;

public:
    Camera(SDL2pp::Point corner) : m_viewBox(corner,SDL2pp::Point(GAME_WIDTH, GAME_HEIGHT)) {}
    void update(SDL_Event &event);
    SDL2pp::Point getPosicion();
    SDL2pp::Rect getViewBox();
};


#endif //DUNE_CAMERA_H
