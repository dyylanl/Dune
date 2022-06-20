//
// Created by riclui on 20/06/22.
//

#include "Button.h"

void Button::draw(SDL2pp::Renderer &renderer) {
    m_textureManager.draw(renderer, m_name, m_position, m_size, SDL_FLIP_NONE);
}
