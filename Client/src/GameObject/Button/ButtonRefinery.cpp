//
// Created by riclui on 20/06/22.
//

#include "ButtonRefinery.h"

ButtonRefinery::ButtonRefinery(SDL2pp::Point position, SDL2pp::Point size)
        : Button("ButtonRefinery", position, size) {}

void ButtonRefinery::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
