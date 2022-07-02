//
// Created by riclui on 26/06/22.
//

#include "HeavyFactoryCL.h"

HeavyFactoryCL::HeavyFactoryCL(int id, int player, SDL2pp::Point position, int life)
        : BuildCL(HEAVY_FACTORY,position, SDL2pp::Point(90,87), id, player, life) {}

void HeavyFactoryCL::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL2pp::Point posFrame1(98,0);
    textureManager.drawFrame(renderer, m_textureID, m_position, m_size, posFrame1);
    SDL2pp::Point posFrame2(0,0);
    textureManager.drawFrame(renderer, m_textureID, m_position + SDL2pp::Point(-20,5), m_size, posFrame2);
}
