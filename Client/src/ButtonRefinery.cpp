//
// Created by riclui on 20/06/22.
//

#include "ButtonRefinery.h"

ButtonRefinery::ButtonRefinery(TextureManager &textureManager, SDL2pp::Point position, SDL2pp::Point size)
        : m_textureManager(textureManager), m_name("buttonRefinery"), m_position(position), m_size(size) {
    m_textureManager.load("buttonRefinery", DATA_PATH "assets/refinery.gif");
}

void ButtonRefinery::draw(SDL2pp::Renderer &renderer) {
    m_textureManager.draw(renderer, m_name, m_position, m_size);
}

SDL2pp::Rect ButtonRefinery::getShape() {
    return SDL2pp::Rect(m_position, m_size);
}
