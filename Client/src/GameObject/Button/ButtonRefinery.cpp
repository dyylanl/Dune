//
// Created by riclui on 20/06/22.
//

#include "ButtonRefinery.h"

ButtonRefinery::ButtonRefinery(int id, char player, int constructionTime)
        : Button("ButtonRefinery", SDL2pp::Point(1089, 120),id, player, constructionTime) {}

void ButtonRefinery::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
