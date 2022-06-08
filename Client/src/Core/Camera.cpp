//
// Created by riclui on 07/06/22.
//

#include "Camera.h"

void Camera::update(EventManager &eventManager) {
    if(eventManager.GetKeyDown(SDL_SCANCODE_LEFT)) {
        position = position - SDL2pp::Point(3,0);
    }
    if(eventManager.GetKeyDown(SDL_SCANCODE_RIGHT)) {
        position = position - SDL2pp::Point(-3,0);
    }
    if(eventManager.GetKeyDown(SDL_SCANCODE_UP)) {
        position = position - SDL2pp::Point(0,3);
    }
    if(eventManager.GetKeyDown(SDL_SCANCODE_DOWN)) {
        position = position - SDL2pp::Point(0,-3);
    }
}

SDL2pp::Point Camera::getPosicion() {
    return position;
}
