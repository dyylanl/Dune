//
// Created by riclui on 07/06/22.
//

#include "Camera.h"

void Camera::update(SDL_Event &event) {
    if(event.motion.x < 80 && m_viewBox.GetX() < 0) {
        m_viewBox = m_viewBox + SDL2pp::Point(2, 0);
    }
    if(event.motion.y < 60 && m_viewBox.GetY() < 0) {
        m_viewBox = m_viewBox + SDL2pp::Point(0, 2);
    }
    if(event.motion.x > GAME_WIDTH - 80 && event.motion.x < GAME_WIDTH) {
        m_viewBox = m_viewBox - SDL2pp::Point(2, 0);
    }
    if(event.motion.y > GAME_HEIGHT - 60) {
        m_viewBox = m_viewBox - SDL2pp::Point(0, 2);
    }
}

SDL2pp::Point Camera::getPosicion() {
    return m_viewBox.GetTopLeft();
}
