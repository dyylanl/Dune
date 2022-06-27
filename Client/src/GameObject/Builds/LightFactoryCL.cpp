//
// Created by riclui on 26/06/22.
//

#include "LightFactoryCL.h"

LightFactoryCL::LightFactoryCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL("LightFactory",position, SDL2pp::Point(99,89), id, player, life) {}

void LightFactoryCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame);
}
