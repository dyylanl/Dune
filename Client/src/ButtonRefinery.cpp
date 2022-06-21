//
// Created by riclui on 20/06/22.
//

#include "ButtonRefinery.h"

ButtonRefinery::ButtonRefinery(SDL2pp::Point position, SDL2pp::Point size)
        : m_name("buttonRefinery"), m_position(position), m_size(size) {}

void ButtonRefinery::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_name, m_position, m_size);
}

SDL2pp::Rect ButtonRefinery::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}
