//
// Created by riclui on 26/06/22.
//

#include "LightFactoryCL.h"

LightFactoryCL::LightFactoryCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(LIGHT_FACTORY,position, SDL2pp::Point(98,66), id, player, life) {}

void LightFactoryCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame1(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame1);
    SDL2pp::Point posFrame2(100,0);
    textureManager.drawFrame(renderer, m_textureID, m_position + SDL2pp::Point(0,0), m_size, posFrame2);
}
