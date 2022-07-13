//
// Created by riclui on 07/06/22.
//

#include "Camera.h"

void Camera::update(SDL_Event &event) {
    // Faltaria chequear que no me vaya de los limites del mapa
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                m_viewBox += SDL2pp::Point(5,0);
                break;
            case SDLK_RIGHT:
                m_viewBox -= SDL2pp::Point(5,0);
                break;
            case SDLK_UP:
                m_viewBox += SDL2pp::Point(0,5);
                break;
            case SDLK_DOWN:
                m_viewBox -= SDL2pp::Point(0,5);
                break;
        }
    }
}

SDL2pp::Point Camera::getPosicion() {
    return m_viewBox.GetTopLeft();
}

SDL2pp::Rect Camera::getViewBox() {
    return m_viewBox;
}
