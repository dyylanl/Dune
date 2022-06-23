//
// Created by riclui on 20/06/22.
//

#include "ButtonWidtrap.h"

ButtonWidtrap::ButtonWidtrap(int id, char player, int constructionTime)
: Button("ButtonWidtrap", id, player, constructionTime) {}

void ButtonWidtrap::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}