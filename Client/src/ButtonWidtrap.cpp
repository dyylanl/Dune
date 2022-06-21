//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrap.h"

void ButtonWidtrap::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_name, m_position, m_size);
}

ButtonWidtrap::ButtonWidtrap(SDL2pp::Point position, SDL2pp::Point size)
: m_name("menuWidtrap"), m_position(position), m_size(size) {}
