//
// Created by riclui on 23/06/22.
//

#include "ButtonYardCL.h"

ButtonYardCL::ButtonYardCL(int id, char player, int constructionTime)
: Button("ButtonYard",id, player, constructionTime) {}

void ButtonYardCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.draw(renderer, m_textureID, m_position, m_size);
}
